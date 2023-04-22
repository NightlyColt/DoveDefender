// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp/EffectComponent.h"
#include "Actors/EffectsFire.h"
// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEffectComponent::StartEffect(EDamageTypes Type, AActor* DamageCauser)
{
	switch (Type)
	{
	case UEffectComponent::Fire:
	{
		FTransform Transform = GetComponentTransform();
		FActorSpawnParameters Params;
		Params.Owner = DamageCauser;

		auto temp = GetWorld()->SpawnActor<AEffectsFire>(AEffectsFire::StaticClass(), Transform, Params);
		AActor* player = GetOwner();
		temp->AttachToActor(player, FAttachmentTransformRules::KeepWorldTransform);
	}
		break;
	case UEffectComponent::NumEffects:
		break;
	default:
		break;
	}
}


// Called every frame
void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

