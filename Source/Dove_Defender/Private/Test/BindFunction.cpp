// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/BindFunction.h"
#include "../../Dove_Defender.h"
// Sets default values
ABindFunction::ABindFunction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Value = 0.65f;
	TimeCallFunction = 2.f;
	OnDefault.AddDynamic(this, &ABindFunction::BindInCode);
}

// Called when the game starts or when spawned
void ABindFunction::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ABindFunction::TimerCompleted, TimeCallFunction, false);
}

// Called every frame
void ABindFunction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABindFunction::BlueprintCallable()
{
	UE_LOG(Game, Warning, TEXT("in C++"));
}

void ABindFunction::BlueprintNativeEvent_Implementation()
{
	UE_LOG(Game, Warning, TEXT("in C++ Native"));
}
float ABindFunction::Pure() const
{
	return Value;
}

void ABindFunction::TimerCompleted()
{
	OnDefault.Broadcast(this); //Call
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("This is broadcasting"));
}

void ABindFunction::BindInCode(AActor* Actor)
{
	UE_LOG(Game, Warning, TEXT("in C++ in Code"));

}

