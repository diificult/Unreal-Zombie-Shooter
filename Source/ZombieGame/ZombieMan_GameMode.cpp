// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieMan_GameMode.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

AZombieMan_GameMode::AZombieMan_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AZombieMan_GameMode::BeginPlay() {
	Super::BeginPlay();
	FTimerHandle UnusedHandle;
	FTimerHandle UnusedHandle2;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AZombieMan_GameMode::SpawnPlayerRecharge, FMath::RandRange(2, 5), true);
	GetWorldTimerManager().SetTimer(UnusedHandle2, this, &AZombieMan_GameMode::SpawnEnemy, FMath::RandRange(1, 3), true);
}

void AZombieMan_GameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AZombieMan_GameMode::SpawnPlayerRecharge()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);
	
	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0, 0, 0);

	GetWorld()->SpawnActor(PlayerRecharge, &SpawnPosition, &SpawnRotation);

}

void AZombieMan_GameMode::SpawnEnemy()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z - 200.f);
	FRotator SpawnRotation = FRotator(0, 0, 0);

	GetWorld()->SpawnActor(Enemy, &SpawnPosition, &SpawnRotation);

}
