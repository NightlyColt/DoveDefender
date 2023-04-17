// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu.h"
#include "Components/Image.h"
#include "Widgets/MyButton.h"
#include "GameInstances/MainGameInstance.h"
#include "Components/Spacer.h"
UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UMainMenu::NativePreConstruct()
{
	auto temp = Cast<UMainGameInstance>(GetGameInstance());
	if (temp)
	{
		GameInstance = temp;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("We need the correct game instance"));
	}
	
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	StartButton->ButtonText = FText::FromString(TEXT("Start"));
	QuitButton->ButtonText = FText::FromString(TEXT("Quit"));

	StartButton->OnButtonClick.AddDynamic(this, &UMainMenu::HandleLoadFirstLevel);
	QuitButton->OnButtonClick.AddDynamic(this, &UMainMenu::HandleQuit);
}

void UMainMenu::HandleQuit()
{
	GameInstance->Quit();
}

void UMainMenu::HandleLoadFirstLevel()
{
	GameInstance->LoadFirstLevel();
}
