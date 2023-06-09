// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/MyUserWidget.h"
#include "Comp/HealthComponent.h"
#include "Components/ActorComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include "DrawDebugHelpers.h"
#include "Actors/BaseWeapon.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Actors/StickyWeapon.h"
#include "Comp/EffectComponent.h"

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	HUD = CreateWidget<UMyUserWidget>(PlayerController, WidgetClass);
	HUD->AddToViewport(0);
	HealthComp->OnDamaged.AddDynamic(this, &ABasePlayer::SetHealth);
	HealthComp->OnDeath.AddDynamic(this, &ABasePlayer::SetHealth);
	CurrentWeapon->Reload();
}

void ABasePlayer::CharacterDeathFinished()
{
	Super::CharacterDeathFinished();
	OnDeathFinished.Broadcast();
}

void ABasePlayer::CharacterHeal(float Ratio)
{
	Super::CharacterHeal(Ratio);
	HUD->SetHealth(Ratio);
}

void ABasePlayer::CharacterAmmoChanged(float Current, float Max)
{
	Super::CharacterAmmoChanged(Current, Max);
	HUD->SetAmmo(Current, Max);
}

bool ABasePlayer::CanPickupHealth()
{
	return !HealthComp->IsFullHealth();
}

bool ABasePlayer::CanPickupClip()
{
	return true;
}

void ABasePlayer::AddClipSize(float AmountToAdd)
{
	CurrentWeapon->AddToClipSize(AmountToAdd);
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

	Weapon1 = ABaseWeapon::StaticClass();
	Weapon2 = AStickyWeapon::StaticClass();
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("TurnTo", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &ABasePlayer::MoveRight);

	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ABasePlayer::CharacterShoot);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ABasePlayer::CharacterReload);
	PlayerInputComponent->BindAction("SwapWeapon", EInputEvent::IE_Pressed, this, &ABasePlayer::SwapChildActorClass);
	PlayerInputComponent->BindAction("SuperPower", EInputEvent::IE_Pressed, this, &ABasePlayer::SuperPower);

}

void ABasePlayer::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ABasePlayer::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ABasePlayer::SwapChildActorClass()
{
	if (WeaponClass == Weapon1)
	{
		WeaponClass = Weapon2;
	}
	else
	{
		WeaponClass = Weapon1;
	}
	CharacterSwapWeapon();
}

void ABasePlayer::SuperPower()
{
	CurrentWeapon->HandleSpecialPower();
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

void ABasePlayer::WonLevel()
{
	DisableInput(PlayerController);
	HUD->RemoveFromParent();
	Movement->StopMovementImmediately();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

FRotator ABasePlayer::GetBaseAimRotation() const
{
	FVector Destination;
	bool Valid;
	FVector HitLocation;
	FVector EndPoint;
	HUD->GetAimedPoint(Valid, HitLocation, EndPoint);

	if (Valid)
	{
		Destination = HitLocation;
		if (HitLocation.ContainsNaN())
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "HitLocation is NaN");

	}
	else
	{
		Destination = EndPoint;
		if (EndPoint.ContainsNaN())
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Endpoint is NaN");

	}

	FVector Result = Destination - CurrentWeapon->SkeletalMesh->GetSocketLocation("MuzzleFlashSocket");
	/*DrawDebugLine(GetWorld(), CurrentWeapon->SkeletalMesh->GetSocketLocation("MuzzleFlashSocket"), Destination, FColor::Green, true, -1, 0, 1);*/

	return UKismetMathLibrary::MakeRotFromX(Result);
}

void ABasePlayer::CharacterSwapWeapon()
{
	Super::CharacterSwapWeapon();

	int index;
	TSubclassOf<URifleAnim> temp;
	CurrentWeapon->GetWeaponInfo(temp, index);
	HUD->SetIconIndex(index);
}


