// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/MyUserWidget.h"
#include "Comp/HealthComponent.h"
#include "Components/ActorComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

void ABasePlayer::BeginPlay() 
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	HUD = CreateWidget<UMyUserWidget>(PlayerController, WidgetClass);
	HUD->AddToViewport(0);
	HealthComp->OnDamaged.AddDynamic(this, &ABasePlayer::SetHealth);
	HealthComp->OnDeath.AddDynamic(this, &ABasePlayer::SetHealth);
}

ABasePlayer::ABasePlayer() 
{
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

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("TurnTo", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &ABasePlayer::MoveRight);

	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ABasePlayer::CharacterShoot);

}

void ABasePlayer::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ABasePlayer::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ABasePlayer::SetHealth(float Ratio)
{
	HUD->SetHealth(Ratio);
}

void ABasePlayer::CharacterDeath(float Ratio)
{
	DisableInput(PlayerController);
	Super::CharacterDeath(0);
	HUD->RemoveFromParent();
}

void ABasePlayer::CharacterDamaged(float Ratio)
{
	Super::CharacterDamaged(0);
	HUD->SetHealth(Ratio);
}
