// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskTargetShoot.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UTaskTargetShoot : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	AAIController* OwnerController;
	APawn* ControlledPawn;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
