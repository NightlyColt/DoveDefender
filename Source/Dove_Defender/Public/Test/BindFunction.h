// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BindFunction.generated.h"

using namespace UP;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDispatcher, AActor*, ParamName);
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

	// Pure
	float Value = 0.4;
	UFUNCTION(BlueprintCallable, Category = "Function|Pure")
	float Pure() const;

	// EventDispatcher
	UPROPERTY(BlueprintCallable, Category = "Function")
	FEventDispatcher OnAction;
	UPROPERTY(BlueprintAssignable, Category = "Function")
	FEventDispatcher OnAssignable;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FEventDispatcher OnDefault;

	// Bind and timer
	float TimeCallFunction;
	// will crash without UFUNCTION
	UFUNCTION()
	void TimerCompleted();
	// will crash without UFUNCTION
	UFUNCTION()
	void BindInCode(AActor* Actor);
};
