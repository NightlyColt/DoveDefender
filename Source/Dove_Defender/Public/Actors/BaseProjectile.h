// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class DOVE_DEFENDER_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class UProjectileMovementComponent* Movement;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;

	FTimerHandle DestroyTimerHandle;
public:
	// Bind and timer
	UPROPERTY(BlueprintReadWrite, Category = "Variables")
	float TimeToDestroy;
	UFUNCTION()
	void TimerEnded();
	UFUNCTION()
	void HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void SpecialPower();

};
