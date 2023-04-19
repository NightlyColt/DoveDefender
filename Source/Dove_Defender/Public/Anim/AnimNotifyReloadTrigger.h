// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/AnimNotifyTrigger.h"
#include "AnimNotifyReloadTrigger.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UAnimNotifyReloadTrigger : public UAnimNotifyTrigger
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
