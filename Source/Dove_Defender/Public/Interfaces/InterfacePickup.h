// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfacePickup.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfacePickup : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DOVE_DEFENDER_API IInterfacePickup
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool CanPickupHealth() = 0;
	virtual bool CanPickupClip() = 0;
	virtual void AddClipSize(float AmountToAdd) = 0;
};
