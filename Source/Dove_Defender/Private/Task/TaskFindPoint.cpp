// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/TaskFindPoint.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include <NavigationSystem.h>
#include <BehaviorTree/BTFunctionLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>

UTaskFindPoint::UTaskFindPoint()
{
	OwnerController = nullptr;
	ControlledPawn = nullptr;
	OutputVector = FBlackboardKeySelector();
}

EBTNodeResult::Type UTaskFindPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerController = OwnerComp.GetAIOwner();
	ControlledPawn = OwnerController->GetPawn();
	UBlackboardComponent* tempB = OwnerComp.GetBlackboardComponent();
	const UBTNode* ActiveNode = OwnerComp.GetActiveNode();
	if (tempB == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT(""));
	}
	FVector Result;
	if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(GetWorld(), ControlledPawn->GetActorLocation(), Result, Radius))
	{
		UE_LOG(LogTemp, Warning, TEXT("Expected Dest: %s"), *Result.ToString());
		tempB->SetValue<UBlackboardKeyType_Vector>(OutputVector.SelectedKeyName, Result);
		//UBTFunctionLibrary::SetBlackboardValueAsVector(OwnerComp.FindTemplateNode(ActiveNode), OutputVector, Result);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't Find a Location"));
	}

	return EBTNodeResult::Failed;
}