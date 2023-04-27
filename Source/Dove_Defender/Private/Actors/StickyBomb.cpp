// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StickyBomb.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

AStickyBomb::AStickyBomb()
{
	DamageRadius = 500;
}

void AStickyBomb::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult)
{
	if (auto temp = Cast<USkeletalMeshComponent>(OtherComp))
	{
		AttachToComponent(temp, FAttachmentTransformRules::KeepWorldTransform, SweepResult.BoneName);
		Movement->StopMovementImmediately();
		UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(GetWorld(), DestroyTimerHandle);
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

void AStickyBomb::SpecialPower()
{
	Super::SpecialPower();

	TArray<AActor*> ignore;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, NULL, ignore, this, GetInstigatorController());
	Destroy();
}
