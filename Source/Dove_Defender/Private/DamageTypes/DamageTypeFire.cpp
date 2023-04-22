// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/DamageTypeFire.h"
#include "Comp/EffectComponent.h"
void UDamageTypeFire::StartEffect(AActor* DamageActor, AActor* DamageCauser) const
{
	if (DamageActor->GetComponentByClass(UEffectComponent::StaticClass()) != nullptr)
	{
		auto temp = Cast<UEffectComponent>(DamageActor->GetComponentByClass(UEffectComponent::StaticClass()));
		if (temp)
			temp->StartEffect(temp->Fire, DamageCauser);
	}
}
