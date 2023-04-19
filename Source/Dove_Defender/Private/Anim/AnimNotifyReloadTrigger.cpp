// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/AnimNotifyReloadTrigger.h"
#include "Anim/RifleAnim.h"

void UAnimNotifyReloadTrigger::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	URifleAnim* anim = Cast<URifleAnim>(MeshComp->GetAnimInstance());
	if (nullptr != anim)
	{
		anim->OnReloadWeapon.Broadcast();
	}
}
