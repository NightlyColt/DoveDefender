// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BindFunction.generated.h"
using namespace UP;
UCLASS()
class DOVE_DEFENDER_API ABindFunction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABindFunction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Function")
	void BlueprintCallable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Function")
	void BlueprintNativeEvent();
	virtual void BlueprintNativeEvent_Implementation();
};
