// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Actors/BaseWeapon.h"
#include "Anim/RifleAnim.h"
#include "Components/ChildActorComponent.h"
#include "Comp/HealthComponent.h"

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
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<ABaseWeapon> WeaponClass;
	WeaponClass = ABaseWeapon::StaticClass();

	WeaponChild->SetChildActorClass(WeaponClass);
	
	CurrentWeapon = Cast<ABaseWeapon>(WeaponChild->GetChildActor());

	if (nullptr == CurrentWeapon)
	{
		UE_LOG(LogTemp, Error, TEXT("There's No Weapon To Use"));
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Found a Weapon"));

		AnimBP = Cast<URifleAnim>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimBP)
		{
			UE_LOG(LogTemp, Error, TEXT("Animation Class Unvalid"));
		}
		else
		{
			CurrentWeapon->OnShoot.AddDynamic(this, &ABaseCharacter::PlayShootAnim);
			AnimBP->OnActionCompleteD.AddDynamic(this, &ABaseCharacter::StopShootAnim);
		}

	}
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

void ABaseCharacter::CharacterShoot()
{
	if (CurrentWeapon != nullptr)
		CurrentWeapon->Shoot();
	else
		UE_LOG(LogTemp, Error, TEXT("There's No Weapon To Use"));
}

void ABaseCharacter::PlayShootAnim()
{
	AnimBP->PlayShootAnim();
}

void ABaseCharacter::StopShootAnim()
{
	CurrentWeapon->StopAnimation();
}

