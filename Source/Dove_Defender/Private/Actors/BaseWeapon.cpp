// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"
#include "Actors/BaseProjectile.h"
#include "Actors/BaseCharacter.h"
#include "Anim/RifleAnim.h"

#include "Components/SkeletalMeshComponent.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMesh);

	WeaponInformation.WeaponInfo = URifleAnim::StaticClass();
	Current = 0;
	Max = 5;
	NewClipSize = -1;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	OwningActor = Cast<APawn>(GetParentActor());
	if (nullptr == OwningActor)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "No parent attached");

	Reload();
}

void ABaseWeapon::HandleSpecialPower()
{
}

void ABaseWeapon::UseAmmo()
{
	Current = FMath::Clamp<float>(Current - 1, 0, Max);
	OnAmmoChanged.Broadcast(Current, Max);
}

AActor* ABaseWeapon::Shoot()
{
	if (CanShoot())
	{
		FTransform Transforms;
		Transforms.SetLocation(SkeletalMesh->GetSocketLocation("MuzzleFlashSocket"));
		Transforms.SetRotation(FQuat(OwningActor->GetBaseAimRotation()));

		FActorSpawnParameters Params;
		Params.Owner = OwningActor->GetController();
		Params.Instigator = OwningActor;
		AActor* proj = GetWorld()->SpawnActor<AActor>(Projectile, Transforms, Params);
		DoShoot = true;
		OnShoot.Broadcast(); // Call
		UseAmmo();
		
		return proj;
	}
	else
	{
		return nullptr;
	}
}

bool ABaseWeapon::CanShoot() const
{
	return !DoShoot && !Dead && (Current > 0);
}

void ABaseWeapon::StopAnimation()
{
	DoShoot = false;
}

void ABaseWeapon::Reload()
{
	if (NewClipSize > 0)
	{
		Max = NewClipSize;
		NewClipSize = -1;
	}
	Current = Max;
	OnAmmoChanged.Broadcast(Current, Max);
}

void ABaseWeapon::CheckStartReload()
{
	if (!DoShoot)
	{
		DoShoot = true;
		OnStartReload.Broadcast();
	}
}

void ABaseWeapon::GetWeaponInfo(TSubclassOf<URifleAnim>& _WeaponInfo, int& HudIndex)
{
	_WeaponInfo = WeaponInformation.WeaponInfo;
	HudIndex = WeaponInformation.HudIndex;
}

void ABaseWeapon::AddToClipSize(float Amount)
{
	NewClipSize = Amount + Max;
	Reload();
}

