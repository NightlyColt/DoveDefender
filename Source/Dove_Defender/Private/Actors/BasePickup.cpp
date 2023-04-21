// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePickup.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABasePickup::ABasePickup()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collsion");
	SetRootComponent(Collision);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::HandleBeginOverlap);

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	ParticleSystem->SetupAttachment(Collision);
}

void ABasePickup::HandleNoPickup()
{
}

void ABasePickup::HandlePostPickup()
{
	Destroy();
}

void ABasePickup::HandlePickup(AActor* other, FHitResult SweepResult)
{
}

bool ABasePickup::ShouldActivate(AActor* other)
{
	return true;
}

void ABasePickup::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ShouldActivate(OtherActor))
	{
		HandlePickup(OtherActor, SweepResult);
		HandlePostPickup();
	}
	else
	{
		HandleNoPickup();
	}
}

