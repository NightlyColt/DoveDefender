// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/HealthPickup.h"
#include "Interfaces/InterfacePickup.h"
#include "Sound/SoundBase.h"
#include <Kismet/GameplayStatics.h>
void AHealthPickup::HandlePostPickup()
{
	Destroy();
}

bool AHealthPickup::ShouldActivate(AActor* other)
{
	auto temp = Cast<IInterfacePickup>(other);
	if (temp)
	{
		return temp->CanPickupHealth();
	}
	return false;
}

void AHealthPickup::HandleNoPickup()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
}
