// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "AIController.h"
#include "BrainComponent.h"
void ABaseAI::Shoot()
{
	CharacterShoot();
}

void ABaseAI::CharacterDeath(float Ratio)
{
	Super::CharacterDeath(Ratio);
	auto controller = UAIBlueprintHelperLibrary::GetAIController(this);

	controller->BrainComponent->StopLogic("AI is Dead");
}

void ABaseAI::CharacterDeathFinished()
{
	Super::CharacterDeathFinished();
	Destroy();
}

