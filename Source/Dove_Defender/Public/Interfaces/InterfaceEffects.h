// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceEffects.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceEffects : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DOVE_DEFENDER_API IInterfaceEffects
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void StartEffect(AActor* DamageActor, AActor* DamageCauser) = 0;
};
