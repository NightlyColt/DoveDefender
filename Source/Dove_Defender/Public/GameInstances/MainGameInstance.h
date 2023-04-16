// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> Levels;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int FirstLevelIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CurrentLevelIndex;

	void LoadLevelSafe(int index);

public:
	UFUNCTION(BlueprintCallable)
	void LoadFirstLevel();
	UFUNCTION(BlueprintCallable)
	void ReloadLevel();
	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();
	UFUNCTION(BlueprintCallable)
	void Quit();
};
