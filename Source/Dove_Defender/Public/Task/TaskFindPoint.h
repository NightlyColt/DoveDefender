// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskFindPoint.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DOVE_DEFENDER_API UTaskFindPoint : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	AAIController* OwnerController;
	APawn* ControlledPawn;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UTaskFindPoint();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector OutputVector;
};
