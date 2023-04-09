// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OtherProjectile.generated.h"

UCLASS()
class DOVE_DEFENDER_API AOtherProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOtherProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		class USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		class UProjectileMovementComponent* Movement;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		class UStaticMeshComponent* Mesh;

public:
	// Bind and timer
	UPROPERTY(BlueprintReadWrite, Category = "Variables")
		float TimeToDestroy;
	UFUNCTION()
		void TimerEnded();
	UFUNCTION()
		void HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
