// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ABasePlayer::ABasePlayer() {
	// Setup Spring
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetWorldLocation(FVector(0.f, 0.f, 65.f));
	SpringArm->bUsePawnControlRotation = true;

	// Setup Camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetWorldLocation(FVector(30.f, 110.f, -5.f));
	// Setup Mesh
	GetMesh()->SetWorldLocation(FVector(0.f, 0.f, -90.f));
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