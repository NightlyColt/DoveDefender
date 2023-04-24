// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InterfacePickup.h"
#include "BaseCharacter.generated.h"

UCLASS()
class  DOVE_DEFENDER_API ABaseCharacter : public ACharacter, public IInterfacePickup
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void CharacterDeathFinished();
	UFUNCTION(BlueprintCallable)
	void CharacterShoot();
	void CharacterReload();
	UFUNCTION()
	virtual void CharacterAmmoChanged(float Current, float Max);
	UFUNCTION()
	virtual void CharacterWeaponActionEnded();
	UFUNCTION()
	virtual void CharacterHeal(float Ratio);
	virtual bool CanPickupHealth();
	virtual void CharacterSwapWeapon();
	void SetReferences();
	void BindEvents();
	void BindWeaponAndAnimationEvents();


	UFUNCTION()
	void PlayReloadAnim();
	UFUNCTION()
	void Reload();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UChildActorComponent* WeaponChild;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABaseWeapon* CurrentWeapon;
	TSubclassOf<ABaseWeapon> WeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseWeapon> Weapon1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AStickyWeapon> Weapon2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class URifleAnim* AnimBP;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthComponent* HealthComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UEffectComponent* EffectComp;

	UPawnMovementComponent* Movement;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void PlayShootAnim();

	UFUNCTION()
	void StopShootAnim();

	UFUNCTION()
	virtual void CharacterDeath(float Ratio);
	UFUNCTION()
	virtual void CharacterDamaged(float Ratio);
};
