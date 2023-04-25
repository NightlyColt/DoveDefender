// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StickyWeapon.h"
#include <Actors/StickyBomb.h>
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
