// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ClipSizePickup.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/InterfacePickup.h"
#include "Sound/SoundBase.h"
#include <Kismet/GameplayStatics.h>
AClipSizePickup::AClipSizePickup()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionProfileName("NoCollision");
}

void AClipSizePickup::HandlePickup(AActor* other, FHitResult SweepResult)
{
	IInterfacePickup* temp = Cast<IInterfacePickup>(other);
	if (temp)
	{
		temp->AddClipSize(AmountToAdd);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
	}
}

bool AClipSizePickup::ShouldActivate(AActor* other)
{
	IInterfacePickup* temp = Cast<IInterfacePickup>(other);
	if (temp)
	{
		return temp->CanPickupClip();
	}
	return false;
}
