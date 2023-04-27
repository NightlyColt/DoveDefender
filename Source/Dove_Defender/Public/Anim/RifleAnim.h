// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RifleAnim.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FADispatcher);

UCLASS()
class DOVE_DEFENDER_API URifleAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	URifleAnim();
	UFUNCTION(BlueprintCallable)
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	///////////////////////////////////////////////////////////////////////////////////
	// UFunctions
	UFUNCTION()
	void OnActionComplete();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Function")
	void PersonaUpdate();
	void virtual PersonaUpdate_Implementation();

	UFUNCTION(BlueprintCallable)
	void PlayShootAnim();

	UFUNCTION(BlueprintCallable)
	void PlayReloadAnim();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Function")
	void PlayDeathAnim(float Ratio);
	void PlayDeathAnim_Implementation(float Ratio);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayHitAnim();
	void PlayHitAnim_Implementation();


	UAnimSequence* GetRandAnim(TArray<UAnimSequence*>& Animations, int& Index);
	////////////////////////////////////////////////////////////////////////////////////
	// UProperties
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	bool DebugDeath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	bool DebugDamaged;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	bool DebugReload;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animations")
		class UAnimSequenceBase* ShootAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animations")
		class UAnimSequenceBase* ReloadAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animations")
		TArray<UAnimSequence*> DeathAnimations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animations")
		UAnimSequence* CurrentDeath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animations")
		UAnimSequence* HitAnimation;

	UPROPERTY(BlueprintReadOnly, Category = "Animations | DeathIndex")
		int DeathIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UAnimSequence*> HitAnimations;
	void DeathIsFinished();

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FADispatcher OnActionCompleteD;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FADispatcher OnDeathFinished;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FADispatcher OnReloadWeapon;
};
