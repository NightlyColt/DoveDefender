// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class  DOVE_DEFENDER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UChildActorComponent* WeaponChild;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABaseWeapon* CurrentWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class URifleAnim* AnimBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void CharacterShoot();

	UFUNCTION()
	void PlayShootAnim();

	UFUNCTION()
	void StopShootAnim();
};
