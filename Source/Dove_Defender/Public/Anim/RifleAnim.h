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
	void NativeUpdateAnimation(float DeltaSeconds) override;

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
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Function")
	void PlayDeathAnim(float Ratio);
	void PlayDeathAnim_Implementation(float Ratio);

	UFUNCTION(BlueprintCallable)
	void PlayHitAnim();

	UAnimSequence* GetRandAnim(TArray<UAnimSequence*>& Animations, int& Index);
	////////////////////////////////////////////////////////////////////////////////////
	// UProperties
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Direction;

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FADispatcher OnActionCompleteD;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animations")
	class UAnimSequenceBase* ShootAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	bool DebugDeath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	bool DebugDamaged;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animations")
	TArray<UAnimSequence*> DeathAnimations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animations")
	UAnimSequence* CurrentDeath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animations")
	UAnimSequence* HitAnimation;

	UPROPERTY(BlueprintReadOnly, Category = "Animations | DeathIndex")
	int DeathIndex;
};
