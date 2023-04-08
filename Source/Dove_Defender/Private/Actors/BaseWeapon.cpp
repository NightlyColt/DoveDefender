// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"
#include "Actors/BaseProjectile.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(RootComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	OwningActor = Cast<APawn>(GetParentActor());
	if (nullptr == OwningActor)
		UE_LOG(LogTemp, Error, TEXT("No parent attached"));
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseWeapon::CanShoot() const
{
	return !DoShoot;
}

void ABaseWeapon::StopAnimation()
{
	DoShoot = false;
}

void ABaseWeapon::Shoot()
{
	if (CanShoot())
	{
		TSubclassOf<ABaseProjectile> ClassRef;
		ClassRef = ABaseProjectile::StaticClass();

		FTransform Transforms;
		Transforms.SetLocation(SkeletalMesh->GetSocketLocation("MuzzleFlashSocket"));
		Transforms.SetRotation(FQuat(OwningActor->GetBaseAimRotation()));

		FActorSpawnParameters Params;
		Params.Owner = OwningActor->GetController();
		Params.Instigator = OwningActor;
		GetWorld()->SpawnActor<AActor>(ClassRef, Transforms, Params);
		DoShoot = true;
		OnShoot.Broadcast(this);
	}
}

