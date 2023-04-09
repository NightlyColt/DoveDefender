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

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	void MyAction();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Direction;

	UFUNCTION()
	void OnActionComplete();

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FADispatcher OnActionCompleteD;

	void PersonaUpdate();

	class UAnimSequenceBase* Asset;
	void PlayShootAnim();


};
