// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/AnimNotifyTrigger.h"
#include "Anim/RifleAnim.h"

void UAnimNotifyTrigger::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	URifleAnim* anim = Cast<URifleAnim>(MeshComp->GetAnimInstance());
	if (nullptr != anim)
	{
		anim->OnActionComplete();
	}
}