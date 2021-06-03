// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZombieGameGameMode.h"
#include "ZombieGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZombieGameGameMode::AZombieGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
