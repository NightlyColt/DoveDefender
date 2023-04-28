// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CodeAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ACodeAIController::ACodeAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ACodeAIController::TargetPerceptionUpdated);
}

void ACodeAIController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	RunBehaviorTree(BTAsset);
}

void ACodeAIController::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
		Blackboard->SetValueAsObject(KeyName, Actor);
	else
		Blackboard->ClearValue(KeyName);
}
