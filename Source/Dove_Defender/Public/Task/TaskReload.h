// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskReload.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UTaskReload : public UBTTaskNode
{
	GENERATED_BODY()
	AAIController* OwnerController;
	APawn* ControlledPawn;
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess) override;
};
