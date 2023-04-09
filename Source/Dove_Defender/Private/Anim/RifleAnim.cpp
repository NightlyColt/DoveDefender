// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/RifleAnim.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimSequence.h"

URifleAnim::URifleAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimAsset(TEXT("AnimSequence'/Game/END_Starter/Mannequin/A_Fire_Ironsights.A_Fire_Ironsights'"));

	Asset = AnimAsset.Object;
}

void URifleAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (nullptr != Pawn) {
		auto Velocity = Pawn->GetVelocity();
		Speed = Velocity.Size();
		auto Rotation = Pawn->GetActorRotation();
		Direction = CalculateDirection(Velocity, Rotation);
	}
	else
		PersonaUpdate();
}

void URifleAnim::MyAction()
{
	OnActionCompleteD.Broadcast();
}

void URifleAnim::OnActionComplete()
{
	OnActionCompleteD.Broadcast();
}

void URifleAnim::PlayShootAnim()
{
	PlaySlotAnimationAsDynamicMontage(Asset, "Action");
	UE_LOG(LogTemp, Warning, TEXT("Played"));
}

void URifleAnim::PersonaUpdate()
{
	PlayShootAnim();
}
