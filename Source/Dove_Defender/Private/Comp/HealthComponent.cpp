// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Current = Max;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamage);
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetStartHealth()
{
	Current = Max;
}

void UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Current = FMath::Clamp<float>(Current - Damage, 0, Max);
	if (Current > 0)
	{
		float ratio = Current / Max;

		OnDamaged.Broadcast(ratio);
	}
	else 
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::HandleDamage);
		OnDeath.Broadcast(0);
	}
}

