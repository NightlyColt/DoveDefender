// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

UCLASS()
class DOVE_DEFENDER_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	UPROPERTY(BlueprintReadOnly, VIsibleAnywhere)
	class UBoxComponent* Collision;
	UPROPERTY(BlueprintReadOnly, VIsibleAnywhere)
	class UParticleSystemComponent* ParticleSystem;
	virtual void HandleNoPickup();
	virtual void HandlePostPickup();
	virtual void HandlePickup(AActor* other, FHitResult SweepResult);
	virtual bool ShouldActivate(AActor* other);
	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
