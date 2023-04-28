// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOVE_DEFENDER_API UEffectComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEffectComponent();
	enum EDamageTypes
	{
		Fire, NumEffects
	};
protected:

	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Fire")
	TSubclassOf<class AEffectsFire> FireClass;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void StartEffect(EDamageTypes Type, AActor* DamageCauser);

		
};
