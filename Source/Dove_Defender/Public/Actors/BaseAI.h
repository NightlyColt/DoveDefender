// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "Interfaces/InterfaceWeapon.h"
#include "BaseAI.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API ABaseAI : public ABaseCharacter, public IInterfaceWeapon
{
	GENERATED_BODY()
	void CharacterDeathFinished() override;
protected:
	void BeginPlay() override;
	FName AmmoKey;
public:
	void Shoot() override;
	void Reload() override;
	void CharacterDeath(float Ratio) override;
	void CharacterWeaponActionEnded() override;
	void CharacterAmmoChanged(float Current, float Max) override;
};
