// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectsFire.generated.h"

UCLASS()
class DOVE_DEFENDER_API AEffectsFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectsFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamagePerSecond;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UParticleSystemComponent* ParticleSystem;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
