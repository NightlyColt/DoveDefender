// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "AnimNotifyTrigger.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UAnimNotifyTrigger : public UAnimNotify_PlaySound
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
