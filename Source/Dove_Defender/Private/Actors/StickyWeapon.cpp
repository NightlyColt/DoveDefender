// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StickyWeapon.h"
#include <Actors/StickyBomb.h>
#include "Anim/RifleAnim.h"

AStickyWeapon::AStickyWeapon()
{
	// Load the skeletal mesh from memory
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Game/END_Starter/Guns/Launcher/SK_Launcher.SK_Launcher'"));
	if (SkeletalMeshAsset.Succeeded())
	{
		SkeletalMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}

	//AnimInfo.WeaponInfo
	Projectile = AStickyBomb::StaticClass();
	Max = 4;
}

AActor* AStickyWeapon::Shoot()
{
	auto ShotTemp = Cast<ABaseProjectile>(Super::Shoot());
	if (ShotTemp)
	{
		ShotProjectiles.Add(ShotTemp);
		return ShotTemp;
	}
	else
	{
		return nullptr;
	}
}

void AStickyWeapon::HandleSpecialPower()
{
	Super::HandleSpecialPower();
	for (auto& Shot : ShotProjectiles)
	{
		Shot->SpecialPower();
	}
	ShotProjectiles.Empty();
}
