// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathFinished);
UCLASS()
class DOVE_DEFENDER_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	void CharacterDeathFinished() override;
	void CharacterHeal(float Ratio) override;
	void CharacterAmmoChanged(float Current, float Max) override;
	bool CanPickupHealth() override;
	bool CanPickupClip() override;
	void AddClipSize(float AmountToAdd) override;
	void CharacterSwapWeapon() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SwapChildActorClass();
	void SuperPower();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetClass;
	class UMyUserWidget* HUD;

	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	APlayerController* PlayerController;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AStickyWeapon> StickyGun;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<URifleAnim> RifleAnim;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<URifleAnim> StickyWeaponAnim;
public:
	ABasePlayer();
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
	void SetHealth(float Ratio);

	virtual void CharacterDeath(float Ratio) override;
	virtual void CharacterDamaged(float Ratio) override;
	void WonLevel();
	FRotator GetBaseAimRotation() const override;

	// Missing Delegate
	FOnDeathFinished OnDeathFinished;
};
