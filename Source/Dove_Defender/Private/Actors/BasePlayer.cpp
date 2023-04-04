// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "GameFrameWork/SpringArmComponent.h"

ABasePlayer::ABasePlayer() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
}
void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("TurnTo", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &ABasePlayer::MoveRight);

}

void ABasePlayer::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ABasePlayer::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}