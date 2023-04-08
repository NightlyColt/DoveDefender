// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEDispatcher, AActor*, ParamName);
UCLASS()
class DOVE_DEFENDER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

public:	
	// Called every frame
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FEDispatcher OnShoot;
	UFUNCTION(BlueprintCallable)
	bool CanShoot() const;
	void StopAnimation();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool DoShoot;

	UPROPERTY(BlueprintReadOnly)
	APawn* OwningActor;


	void Shoot();
};
