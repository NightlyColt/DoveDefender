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
	
public:
	void Shoot() override;
};
