// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/MainGameInstance.h"
#include <Kismet/GameplayStatics.h>

void UMainGameInstance::LoadLevelSafe(int index)
{
	if (Levels.IsValidIndex(index))
	{
		CurrentLevelIndex = index;
		UGameplayStatics::OpenLevel(GetWorld(), Levels[CurrentLevelIndex], true, TEXT(""));
	}
	else
	{
		FString msg = "Invalid index: ";
		msg.Append(FString::Printf(TEXT("%d"), index));
	}
}

void UMainGameInstance::LoadFirstLevel()
{
	LoadLevelSafe(1);
}

void UMainGameInstance::ReloadLevel()
{
	LoadLevelSafe(CurrentLevelIndex);
}

void UMainGameInstance::LoadMainMenu()
{
	LoadLevelSafe(0);
}

void UMainGameInstance::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
