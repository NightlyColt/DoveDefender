// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "ClipSizePickup.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API AClipSizePickup : public ABasePickup
{
	GENERATED_BODY()
public:
	AClipSizePickup();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float AmountToAdd;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USoundBase* Sound;
	void HandlePickup(AActor* other, FHitResult SweepResult) override;
	bool ShouldActivate(AActor* other) override;
};
