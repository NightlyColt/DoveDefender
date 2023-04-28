// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyButton.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventOnMyButtonClicked);
UCLASS()
class DOVE_DEFENDER_API UMyButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UMyButton(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText ButtonText;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FEventOnMyButtonClicked OnButtonClick;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BackgroundButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Info;

	UFUNCTION()
	void HandleOnButtonClicked();
};
