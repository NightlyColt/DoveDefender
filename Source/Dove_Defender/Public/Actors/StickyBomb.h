// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseProjectile.h"
#include "StickyBomb.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API AStickyBomb : public ABaseProjectile
{
	GENERATED_BODY()
public:
	AStickyBomb();
	void SpecialPower() override;

protected:
	void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageRadius;
};
