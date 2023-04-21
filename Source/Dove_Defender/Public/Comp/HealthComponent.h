// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

using namespace UP;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEOnDispatcher, float, Ratio);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DOVE_DEFENDER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	float Current;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Max;

public:	

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FEOnDispatcher OnDamaged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FEOnDispatcher OnDeath;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FEOnDispatcher OnHealthGained;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	bool IsFullHealth() const;
	void SetStartHealth();

	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
		
};
