// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Background;
	UPROPERTY(BlueprintReadOnly)
	class UVerticalBox* VerticalBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMyButton* StartButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMyButton* QuitButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMainGameInstance* GameInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpacer* Spacer;
	/*UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class MyButton* StartButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	MyButton* QuitButton;*/
	/*UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class SSpacer* Spacer;*/
public:
	virtual void NativePreConstruct() override;
	void NativeConstruct() override;

	UFUNCTION()
	void HandleQuit();
	UFUNCTION()
	void HandleLoadFirstLevel();

};
