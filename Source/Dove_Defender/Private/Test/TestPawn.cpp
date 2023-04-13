// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestPawn.h"
#include "../../Dove_Defender.h"
#include "EngineUtils.h"
#include "Interfaces/DemoInterface.h"
// Sets default values
ATestPawn::ATestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestPawn::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters Params;
	Params.Owner = GetController();
	Params.Instigator = this;

	for (TActorIterator<AActor>itr(GetWorld()); itr; ++itr)
	{
		UDemoInterface* U = Cast<UDemoInterface>(*itr);
		if (nullptr != U)
		{
			UE_LOG(LogTemp, Warning, TEXT("I am U"));
		}
		IDemoInterface* I = Cast<IDemoInterface>(*itr);
		if (nullptr != I)
		{
			I->Shoot();
			UE_LOG(LogTemp, Warning, TEXT("I am I"));

		}
	}
	//GetWorld()->SpawnActor<AActor>(ClassType, FTransform(), Params);
}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ATestPawn::InputHappened);

}

void ATestPawn::InputHappened() 
{
	UE_LOG(Game, Error, TEXT("Input Happened"));
	TSubclassOf<ATestPawn> ClassRef;
	ClassRef = ATestPawn::StaticClass();
	FActorSpawnParameters Params;
	Params.Owner = GetController();
	Params.Instigator = this;
	GetWorld()->SpawnActor<AActor>(ClassRef, FTransform(), Params);
}


