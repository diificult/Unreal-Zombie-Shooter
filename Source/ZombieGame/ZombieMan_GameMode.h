// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ZombieMan_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEGAME_API AZombieMan_GameMode : public AGameMode
{
	GENERATED_BODY()
		AZombieMan_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float time) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> PlayerRecharge;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> Enemy;

	float Spawn_Z = 500.0f;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Min;
	UPROPERTY(EditAnywhere)
		float Spawn_X_Max;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Min;
	UPROPERTY(EditAnywhere)
		float Spawn_Y_Max;

	void SpawnPlayerRecharge();
	void SpawnEnemy();

};
