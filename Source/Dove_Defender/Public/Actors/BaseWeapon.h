// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponSync
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class URifleAnim> WeaponInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int HudIndex;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEDispatcher);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChangedEvent, float, CurrentAmmo, float, MaxAmmo);
UCLASS()
class DOVE_DEFENDER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Current;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Max;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float NewClipSize;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FWeaponSync WeaponInformation;

	// Declare a reference to the projectile that the weapon fires
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> Projectile;
	void UseAmmo();

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;
	// Declare a delegate instance for when the weapon is fired
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FEDispatcher OnShoot;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FOnAmmoChangedEvent OnAmmoChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FEDispatcher OnStartReload;

	// Declare a function to check if the weapon can fire
	UFUNCTION(BlueprintCallable)
	bool CanShoot() const;

	// Declare a function to stop the weapon's animation
	void StopAnimation();

	virtual void HandleSpecialPower();

	// Declare a flag to indicate if the weapon is firing
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool DoShoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Dead;
	// Declare a reference to the owning actor of the weapon
	UPROPERTY(BlueprintReadOnly)
	APawn* OwningActor;

	// Declare a function to fire the weapon
	virtual AActor* Shoot();

	void Reload();

	void CheckStartReload();

	void GetWeaponInfo(TSubclassOf<URifleAnim>& _WeaponInfo, int& HudIndex);

	void AddToClipSize(float Amount);
};
