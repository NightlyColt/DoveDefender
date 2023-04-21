// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DamagePickup.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"

void ADamagePickup::HandlePostPickup()
{
}

void ADamagePickup::HandlePickup(AActor* other, FHitResult SweepResult)
{
	UGameplayStatics::ApplyDamage(other, Damage, nullptr, this, DamageType);
}
