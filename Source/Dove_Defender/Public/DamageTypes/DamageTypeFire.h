// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Interfaces/InterfaceEffects.h"
#include "DamageTypeFire.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UDamageTypeFire : public UDamageType, public IInterfaceEffects
{
	GENERATED_BODY()
public:
	void StartEffect(AActor* DamageActor, AActor* DamageCauser) const override;
};
