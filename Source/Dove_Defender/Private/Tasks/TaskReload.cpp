// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/TaskReload.h"
#include "AIController.h"
#include "Interfaces/InterfaceWeapon.h"
#include <BehaviorTree/BTFunctionLibrary.h>
EBTNodeResult::Type UTaskReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerController = OwnerComp.GetAIOwner();
	ControlledPawn = OwnerController->GetPawn();
	IInterfaceWeapon* tempI = Cast<IInterfaceWeapon>(ControlledPawn);
	if (tempI)
	{
		tempI->Reload();
		WaitForMessage(OwnerComp, "ActionFinished");
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UTaskReload::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess)
{
	if (Message == FName("ActionFinished"))
	{
		// The reload message was received, so return success
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
