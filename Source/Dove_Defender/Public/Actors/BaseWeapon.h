// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEDispatcher);
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

	// Declare a skeletal mesh component for the weapon's mesh
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USkeletalMeshComponent* SkeletalMesh;

public:
	// Declare a delegate instance for when the weapon is fired
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
		FEDispatcher OnShoot;

	// Declare a function to check if the weapon can fire
	UFUNCTION(BlueprintCallable)
		bool CanShoot() const;

	// Declare a function to stop the weapon's animation
	void StopAnimation();

	// Declare a flag to indicate if the weapon is firing
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool DoShoot;

	// Declare a reference to the owning actor of the weapon
	UPROPERTY(BlueprintReadOnly)
		APawn* OwningActor;

	// Declare a reference to the projectile that the weapon fires
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<class ABaseProjectile> Projectile;

	// Declare a function to fire the weapon
	void Shoot();
};