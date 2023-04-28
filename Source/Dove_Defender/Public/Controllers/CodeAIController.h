// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "CodeAIController.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API ACodeAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName KeyName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBehaviorTree* BTAsset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAIPerceptionComponent* AIPerception;

public:
	/*virtual void OnPossess(APawn* aPawn) override;*/
	ACodeAIController();
	virtual void OnPossess(APawn* aPawn) override;
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
