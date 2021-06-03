// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharater.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyBullet.h"

// Sets default values
AMainCharater::AMainCharater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bDead = false;
	Health = 100.0f;
}




// Called when the game starts or when spawned
void AMainCharater::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharater::OnBeginOverlap);
	
	if (Player_Health_Widget_Class != nullptr) {
		Player_Health_Widget = CreateWidget(GetWorld(), Player_Health_Widget_Class);
		Player_Health_Widget->AddToViewport();
	}
}

// Called every frame
void AMainCharater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMainCharater::UntakeDamage, 1.0f, true);
	if (Health <= 0) {
		if (!bDead) {
			bDead = true;
			GetMesh()->SetSimulatePhysics(true);
			FTimerHandle UnusedHandle2;
			GetWorldTimerManager().SetTimer(UnusedHandle2, this, &AMainCharater::RestartGame, 3.0f, false);
		}
	}

}

void AMainCharater::UntakeDamage() {
	TakenDamage = false;
}

// Called to bind functionality to input
void AMainCharater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this,  &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released,this,  &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAxis("MoveForward", this,  &AMainCharater::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this,  &AMainCharater::MoveRight);


	PlayerInputComponent->BindAction("Shoot", IE_Pressed,  this,  &AMainCharater::Shoot);


}

void AMainCharater::MoveForward(float Axis)
{
	if (!bDead) {

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
		

	}
}

void AMainCharater::MoveRight(float Axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);

}
void AMainCharater::Shoot()
{
	FTransform SpawnTransform = GetActorTransform();
	
	SpawnTransform.SetLocation(FollowCamera->GetComponentRotation().Vector() * 200.f + GetActorLocation());
	
	SpawnTransform.TransformPosition(FVector(0.f, 0.f, 100.f));

	FActorSpawnParameters SpawnParams;
	

	GetWorld()->SpawnActor<AMyBullet>(BulletBP, SpawnTransform, SpawnParams);


}
void AMainCharater::OnBeginOverlap(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag("Recharge")) {
		Health += 20.0f;
		if (Health > 100.0f)
			Health = 100.0f;
		OtherActor->Destroy();
	}
	else if (OtherActor->ActorHasTag("Enemy") && TakenDamage == false) {
		Health -= 5.0f;
		TakenDamage = true;
	}
}
void AMainCharater::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
