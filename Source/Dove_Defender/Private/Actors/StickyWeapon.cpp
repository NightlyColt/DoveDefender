// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StickyWeapon.h"
#include <Actors/StickyBomb.h>
#include "Anim/RifleAnim.h"

AStickyWeapon::AStickyWeapon()
{
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
