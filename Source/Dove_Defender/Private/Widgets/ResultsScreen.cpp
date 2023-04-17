// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ResultsScreen.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Widgets/MyButton.h"
#include "GameInstances/MainGameInstance.h"

void UResultsScreen::NativePreConstruct()
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
	MainMenuButton->OnButtonClick.AddDynamic(this, &UResultsScreen::HandleLoadMainMenu);
	PlayAgainButton->OnButtonClick.AddDynamic(this, &UResultsScreen::HandleReloadLevel);

	MainMenuButton->ButtonText = FText::FromString(TEXT("Main Menu"));
	PlayAgainButton->ButtonText = FText::FromString(TEXT("Play Again"));
}

void UResultsScreen::SetWin()
{
	ResultsSwitch->SetActiveWidgetIndex(1);
	ButtonBox->SetVisibility(ESlateVisibility::Hidden);
}

void UResultsScreen::SetLose()
{
	ResultsSwitch->SetActiveWidgetIndex(0);
	ButtonBox->SetVisibility(ESlateVisibility::Visible);
}

void UResultsScreen::HandleLoadMainMenu()
{
	GameInstance->LoadMainMenu();
}

void UResultsScreen::HandleReloadLevel()
{
	GameInstance->ReloadLevel();
}
