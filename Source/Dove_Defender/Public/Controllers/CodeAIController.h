// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CodeAIController.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API ACodeAIController : public AAIController
{
	GENERATED_BODY()
private:
	FName KeyName;
public:
	virtual void OnPossess(APawn* aPawn) override;
};
