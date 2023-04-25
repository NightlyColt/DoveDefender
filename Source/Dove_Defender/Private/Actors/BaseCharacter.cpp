// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Actors/BaseWeapon.h"
#include "Anim/RifleAnim.h"
#include "Components/ChildActorComponent.h"
#include "Comp/HealthComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include <Kismet/KismetMathLibrary.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "Widgets/MyUserWidget.h"
#include "Comp/EffectComponent.h"
#include "Actors/StickyWeapon.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));

	WeaponChild = CreateDefaultSubobject<UChildActorComponent>("WeaponChild");
	WeaponChild->SetupAttachment(GetMesh(), "Weapon_Socket");

	// Setup Mesh
	GetMesh()->SetWorldLocation(FVector(0.f, 0.f, -90.f));
	HealthComp = CreateDefaultSubobject<UHealthComponent>("Health_Component");
	EffectComp = CreateDefaultSubobject<UEffectComponent>("EffectComponent");
	EffectComp->SetupAttachment(GetMesh());
	EffectComp->SetWorldLocation(FVector(0, 0, 140));

	GetMesh()->SetGenerateOverlapEvents(true);
	WeaponClass = ABaseWeapon::StaticClass();
	Movement = GetMovementComponent();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetReferences();
	BindEvents();
}



// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::CharacterDeathFinished()
{
}

void ABaseCharacter::CharacterShoot()
{
	if (CurrentWeapon != nullptr)
		CurrentWeapon->Shoot();
	else
		UE_LOG(LogTemp, Error, TEXT("There's No Weapon To Use"));
}

void ABaseCharacter::CharacterReload()
{
	CurrentWeapon->CheckStartReload();
}

void ABaseCharacter::CharacterAmmoChanged(float Current, float Max)
{
}

void ABaseCharacter::CharacterWeaponActionEnded()
{
	CurrentWeapon->StopAnimation();
}

void ABaseCharacter::CharacterHeal(float Ratio)
{
}

void ABaseCharacter::PlayReloadAnim()
{
	AnimBP->PlayReloadAnim();
}

void ABaseCharacter::Reload()
{
	CurrentWeapon->Reload();
}

void ABaseCharacter::PlayShootAnim()
{
	AnimBP->PlayShootAnim();
}

void ABaseCharacter::StopShootAnim()
{
	CurrentWeapon->StopAnimation();
}

void ABaseCharacter::CharacterDeath(float Ratio)
{
	Movement->StopMovementImmediately();
	AnimBP->PlayDeathAnim(0);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CurrentWeapon->Dead = true;
}

void ABaseCharacter::CharacterDamaged(float Ratio)
{
	AnimBP->PlayHitAnim();
}

bool ABaseCharacter::CanPickupHealth()
{
	return false;
}

void ABaseCharacter::CharacterSwapWeapon()
{
	SetReferences();
	BindWeaponAndAnimationEvents();
	CurrentWeapon->Reload();
}

void ABaseCharacter::SetReferences()				// Look inside here
{
	WeaponChild->SetChildActorClass(WeaponClass);

	CurrentWeapon = Cast<ABaseWeapon>(WeaponChild->GetChildActor());

	if (nullptr == CurrentWeapon)
	{
		UE_LOG(LogTemp, Error, TEXT("There's No Weapon To Use"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Found a Weapon"));
		// Remember to get the weapon info from the current weapon and set the anim instance to that.
		AnimBP = Cast<URifleAnim>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimBP)
		{
			UE_LOG(LogTemp, Error, TEXT("Animation Class Unvalid"));
		}
	}
}

void ABaseCharacter::BindEvents()
{
	// Check if the health component is valid
	if (HealthComp)
	{
		HealthComp->OnDamaged.AddDynamic(this, &ABaseCharacter::CharacterDamaged);
		HealthComp->OnDeath.AddDynamic(this, &ABaseCharacter::CharacterDeath);
		HealthComp->OnHealthGained.AddDynamic(this, &ABaseCharacter::CharacterHeal);
		BindWeaponAndAnimationEvents();
	}
}

void ABaseCharacter::BindWeaponAndAnimationEvents()
{
	// Check if current weapon and animbp are valid
	if (CurrentWeapon && AnimBP)
	{
		CurrentWeapon->OnShoot.AddDynamic(this, &ABaseCharacter::PlayShootAnim);
		AnimBP->OnActionCompleteD.AddDynamic(this, &ABaseCharacter::CharacterWeaponActionEnded);
		AnimBP->OnDeathFinished.AddDynamic(this, &ABaseCharacter::CharacterDeathFinished);
		CurrentWeapon->OnAmmoChanged.AddDynamic(this, &ABaseCharacter::CharacterAmmoChanged);
		CurrentWeapon->OnStartReload.AddDynamic(this, &ABaseCharacter::PlayReloadAnim);
		AnimBP->OnReloadWeapon.AddDynamic(this, &ABaseCharacter::Reload);
	}
}

