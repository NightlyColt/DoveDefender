// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseWeapon.h"
#include "StickyWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API AStickyWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	AStickyWeapon();
protected:
	AActor* Shoot() override;
	void HandleSpecialPower() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<class ABaseProjectile*> ShotProjectiles;
};
