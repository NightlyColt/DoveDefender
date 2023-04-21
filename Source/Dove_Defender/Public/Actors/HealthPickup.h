// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DamagePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API AHealthPickup : public ADamagePickup
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USoundBase* Sound;
	void HandlePostPickup() override;
	bool ShouldActivate(AActor* other) override;
	void HandleNoPickup() override;
};
