// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "DamagePickup.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API ADamagePickup : public ABasePickup
{
	GENERATED_BODY()
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UDamageType> DamageType;
	void HandlePostPickup() override;
	void HandlePickup(AActor* other, FHitResult SweepResult) override;
};
