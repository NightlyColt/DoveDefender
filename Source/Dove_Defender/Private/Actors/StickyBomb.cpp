// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StickyBomb.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/KismetSystemLibrary.h>

AStickyBomb::AStickyBomb()
{
	UMaterialInterface* NewMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Game/Art/MI_Purple.MI_Purple'"), nullptr, LOAD_None, nullptr);
	if (NewMaterial != nullptr)
	{
		Mesh->SetMaterial(0, NewMaterial);
	}
}

void AStickyBomb::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult)
{
	if (Cast<USkeletalMeshComponent>(OtherComp))
	{
		Super::HandleOverlap(OtherActor,  OtherComp, SweepResult);
	}
	else
	{
		switch (OtherComp->GetCollisionObjectType())
		{
		case ECollisionChannel::ECC_WorldStatic:
		{
				Movement->StopMovementImmediately();
				UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(GetWorld(), DestroyTimerHandle);
				TeleportTo(SweepResult.Location, GetActorRotation());
		}
			break;
		default:
			break;	
		}
		
	}
}
