// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamplayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API AGamplayGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGamplayGameMode();
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void EnemyDestroyed(AActor* actor);
	UFUNCTION()
	void PlayerDestroyed();
	UFUNCTION()
	void LoadMainMenu();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int NumberOfEnemies;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerController* ActivePC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UResultsScreen* ResultsWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMainGameInstance* GameInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UResultsScreen> ResultsClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PlayerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToSeeWinScreen;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* ActivePlayer;
};
