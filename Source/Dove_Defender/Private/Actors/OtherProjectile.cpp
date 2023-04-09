// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/OtherProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

// Sets default values
AOtherProjectile::AOtherProjectile()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetCollisionProfileName("Custom");
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AOtherProjectile::HandleCollision);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	/*ConstructorHelpers::FObjectFinder<UStaticMesh>Asset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Mesh->SetStaticMesh(Asset.Object);*/
	UStaticMesh* NewMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"), nullptr, LOAD_None, nullptr);
	UMaterialInterface* NewMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Art/M_FlatColor.M_FlatColor'"), nullptr, LOAD_None, nullptr);
	if (NewMaterial != nullptr)
	{
		Mesh->SetMaterial(0, NewMaterial);
	}
	if (NewMesh != nullptr)
	{
		Mesh->SetStaticMesh(NewMesh);
	}
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	Movement->InitialSpeed = 1800;
	Movement->MaxSpeed = 2000;
	Movement->ProjectileGravityScale = 0.f;

	FVector Scale = FVector(.6f, .6f, .6f);

	Mesh->SetWorldScale3D(Scale);
	Collision->SetWorldScale3D(Scale);
	TimeToDestroy = 3.f;
}

// Called when the game starts or when spawned
void AOtherProjectile::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AOtherProjectile::TimerEnded, TimeToDestroy, false);
	
}

void AOtherProjectile::HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}

void AOtherProjectile::TimerEnded()
{
	Destroy();
}
