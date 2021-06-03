// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiePawn.h"


void AZombiePawn::Hunt()
{
	State = EEnemyState::Default;

	StateChangedEvent.Broadcast(State);


}

void AZombiePawn::Idle()
{
	State = EEnemyState::Idle;

	StateChangedEvent.Broadcast(State);

}
