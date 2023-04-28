// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/BaseWeapon.h"
#include "Comp/EffectComponent.h"

void ABaseAI::Shoot()
{
	CharacterShoot();
}

void ABaseAI::Reload()
{
	CharacterReload();
}

void ABaseAI::CharacterDeath(float Ratio)
{
	Super::CharacterDeath(Ratio);
	auto controller = UAIBlueprintHelperLibrary::GetAIController(this);

	controller->BrainComponent->StopLogic("AI is Dead");
}

void ABaseAI::CharacterWeaponActionEnded()
{
	Super::CharacterWeaponActionEnded();
	UAIBlueprintHelperLibrary::SendAIMessage(this, "ActionFinished", nullptr, true);
}

void ABaseAI::CharacterAmmoChanged(float Current, float Max)
{
	Super::CharacterAmmoChanged(Current, Max);
	auto comp = UAIBlueprintHelperLibrary::GetAIController(this);
	if (comp)
	{
		auto bComp = comp->GetBlackboardComponent();
		if (bComp)
		{
			AmmoKey = "Ammo";
			bComp->SetValueAsFloat(AmmoKey, Current);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "BlackBoard Couldn't be found");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "AIController Couldn't be found");
	}
}

void ABaseAI::CharacterDeathFinished()
{
	Super::CharacterDeathFinished();
	Destroy();
}

void ABaseAI::BeginPlay()
{
	Super::BeginPlay();
	CurrentWeapon->Reload();
}
