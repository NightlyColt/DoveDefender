// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"
using namespace UP;
/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetClass;
	class UMyUserWidget* HUD;
	
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	APlayerController* PlayerController;
public:
	ABasePlayer();
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION()
	void SetHealth(float Ratio);

	virtual void CharacterDeath(float Ratio) override;
	virtual void CharacterDamaged(float Ratio) override;
	FRotator GetBaseAimRotation() const override;

};
