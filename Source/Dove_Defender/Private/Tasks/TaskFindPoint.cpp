// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/TaskFindPoint.h"
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "");

	}
	FVector Result;
	if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(GetWorld(), ControlledPawn->GetActorLocation(), Result, Radius))
	{

		tempB->SetValue<UBlackboardKeyType_Vector>(OutputVector.SelectedKeyName, Result);
		//UBTFunctionLibrary::SetBlackboardValueAsVector(OwnerComp.FindTemplateNode(ActiveNode), OutputVector, Result);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Couldn't Find a Location");

	}

	return EBTNodeResult::Failed;
}