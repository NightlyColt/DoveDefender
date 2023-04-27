// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EffectsFire.h"
#include "Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEffectsFire::AEffectsFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	ParticleSystem->SetupAttachment(GetRootComponent());
	// Deleted Effects Fire Particle effect
	DamagePerSecond = 2.f;
	InitialLifeSpan = 2;
}

// Called when the game starts or when spawned
void AEffectsFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectsFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Damage = DamagePerSecond * DeltaTime;
	UGameplayStatics::ApplyDamage(GetAttachParentActor(), Damage, GetInstigatorController(), GetInstigator(), NULL);
}

