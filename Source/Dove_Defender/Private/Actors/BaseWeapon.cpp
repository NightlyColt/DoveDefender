// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"
#include "Actors/BaseProjectile.h"
#include "Actors/BaseCharacter.h"

#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMesh);

	// Load the skeletal mesh from memory
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Game/END_Starter/Guns/Rifle/SK_Rifle.SK_Rifle'"));
	if (SkeletalMeshAsset.Succeeded())
	{
		SkeletalMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}

	Projectile = ABaseProjectile::StaticClass();

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	OwningActor = Cast<APawn>(GetParentActor());
	if (nullptr == OwningActor)
		UE_LOG(LogTemp, Error, TEXT("No parent attached"));
}

bool ABaseWeapon::CanShoot() const
{
	return !DoShoot;
}

void ABaseWeapon::StopAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("Stoped"));

	DoShoot = false;
}

void ABaseWeapon::Shoot()
{
	if (CanShoot())
	{
		FTransform Transforms;
		Transforms.SetLocation(SkeletalMesh->GetSocketLocation("MuzzleFlashSocket"));
		UE_LOG(LogTemp, Warning, TEXT("I Shot"));
		Transforms.SetRotation(FQuat(OwningActor->GetBaseAimRotation()));
		TSubclassOf<ABaseProjectile> ClassRf;
		ClassRf = ABaseProjectile::StaticClass();

		FActorSpawnParameters Params;
		Params.Owner = OwningActor->GetController();
		Params.Instigator = OwningActor;
		AActor* proj = GetWorld()->SpawnActor<AActor>(Projectile, Transforms, Params);
		DoShoot = true;
		OnShoot.Broadcast(); // Call
	}
}

