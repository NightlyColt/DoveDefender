// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UMyUserWidget(const FObjectInitializer& ObjectInitializer);
protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* Health;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Reticle;

public:
	void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void SetHealth(float ratio);
};
