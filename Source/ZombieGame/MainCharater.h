// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"

#include "MainCharater.generated.h"

UCLASS()
class ZOMBIEGAME_API AMainCharater : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharater();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Health;

	UPROPERTY(EditAnywhere)
		float Health_Threashold;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent * HitComp, 
			class AActor * OtherActor, 
			class UPrimitiveComponent * OtherComp, 
			int32 OtherBoardIndex, 
			bool bFromSweep, 
			const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Player_Health_Widget_Class;
	UUserWidget* Player_Health_Widget;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class AMyBullet> BulletBP;
	
	void RestartGame();

	void UntakeDamage();


	bool TakenDamage = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Shoot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	

	

};
