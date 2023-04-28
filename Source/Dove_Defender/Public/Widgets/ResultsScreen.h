// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultsScreen.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UResultsScreen : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* ResultsSwitch;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* ButtonBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMyButton* PlayAgainButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMyButton* MainMenuButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMainGameInstance* GameInstance;

	virtual void NativePreConstruct() override;

	UFUNCTION()
	void HandleLoadMainMenu();
	UFUNCTION()
	void HandleReloadLevel();

public:
	UFUNCTION(BlueprintCallable)
	void SetWin();
	UFUNCTION(BlueprintCallable)
	void SetLose();
};
