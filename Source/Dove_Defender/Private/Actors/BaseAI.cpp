// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"

void ABaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CharacterShoot();
}
