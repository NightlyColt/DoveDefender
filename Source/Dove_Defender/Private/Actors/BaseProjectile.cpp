// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "../../Dove_Defender.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetCollisionProfileName("Custom");
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::HandleCollision);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionProfileName("NoCollision");
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Mesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	Mesh->SetGenerateOverlapEvents(false);
	Movement->InitialSpeed = 1800;
	Movement->MaxSpeed = 2000;
	Movement->ProjectileGravityScale = 0.f;

	FVector Scale = FVector(.6f, .6f, .6f);

	Mesh->SetWorldScale3D(Scale);
	Collision->SetWorldScale3D(Scale);
	TimeToDestroy = 3.f;
	Damage = 1.f;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ABaseProjectile::TimerEnded, TimeToDestroy, false);

}

void ABaseProjectile::HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleOverlap(OtherActor, OtherComp, SweepResult);
}

void ABaseProjectile::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult)
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), GetInstigator(), UDamageType::StaticClass());
	if (!IsPendingKill())
	{
		Destroy();
	}
}

void ABaseProjectile::SpecialPower()
{
}

void ABaseProjectile::TimerEnded()
{
	if (!IsPendingKill())
		Destroy();
}

