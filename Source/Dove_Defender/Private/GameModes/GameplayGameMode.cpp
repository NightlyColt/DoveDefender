// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GameplayGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "Widgets/ResultsScreen.h"
#include "GameInstances/MainGameInstance.h"
#include "Actors/BasePlayer.h"
#include "Actors/BaseAI.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "Controllers/GamePlayerController.h"
AGameplayGameMode::AGameplayGameMode()
{
}

void AGameplayGameMode::BeginPlay()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, OutActors); // Maybe make the subclass a variable

	NumberOfEnemies = OutActors.Num();
	for (auto& enemy : OutActors)
	{
		enemy->OnDestroyed.AddDynamic(this, &AGameplayGameMode::EnemyDestroyed);
	}
	// Get Active Player
	auto tempPlayer = Cast<ABasePlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), PlayerClass)); // Maybe make the subclass a variable
	if (tempPlayer)
		ActivePlayer = tempPlayer;
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Wrong Active Player");


	ActivePlayer->OnDeathFinished.AddDynamic(this, &AGameplayGameMode::PlayerDestroyed);

	// Get Active Player Controller
	auto tempPC = Cast<AGamePlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), PlayerControllerClass));
	if (tempPC)
		ActivePC = tempPC;
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Wrong Player Controller");


	// Get The Results Widget
	auto tempWidget = Cast<UResultsScreen>(CreateWidget(ActivePC, ResultsClass));
	if (tempWidget)
		ResultsWidget = tempWidget;
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Wrong Results Widget");


	// Get Game Instance
	auto tempInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (tempInstance)
	{
		GameInstance = tempInstance;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Wrong Game Instance");

	}
}

void AGameplayGameMode::EnemyDestroyed(AActor* actor)
{
	if (--NumberOfEnemies == 0)
	{
		ResultsWidget->SetWin();
		ResultsWidget->AddToViewport(0);

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &AGameplayGameMode::LoadMainMenu, TimeToSeeWinScreen, false);
		ActivePlayer->WonLevel();
	}
}

void AGameplayGameMode::PlayerDestroyed()
{
	ResultsWidget->SetLose();
	ActivePC->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_UIOnly(ActivePC, nullptr, true);
	ResultsWidget->AddToViewport(0);
}

void AGameplayGameMode::LoadMainMenu()
{
	GameInstance->LoadMainMenu();
}
