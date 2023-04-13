// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/TaskTargetShoot.h"
#include "AIController.h"
#include "Interfaces/InterfaceWeapon.h"

EBTNodeResult::Type UTaskTargetShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerController = OwnerComp.GetAIOwner();
	ControlledPawn = OwnerController->GetPawn();
	IInterfaceWeapon* tempI = Cast<IInterfaceWeapon>(ControlledPawn);
	if (tempI)
		tempI->Shoot();

	return EBTNodeResult::Succeeded;
}
