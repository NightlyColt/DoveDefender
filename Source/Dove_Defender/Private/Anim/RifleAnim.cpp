// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/RifleAnim.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimSequence.h"

URifleAnim::URifleAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimAsset(TEXT("AnimSequence'/Game/END_Starter/Mannequin/A_Fire_Ironsights.A_Fire_Ironsights'"));

	ShootAnim = AnimAsset.Object;
	DeathIndex = -1;
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

void URifleAnim::OnActionComplete()
{
	OnActionCompleteD.Broadcast();
}

void URifleAnim::PlayShootAnim()
{
	PlaySlotAnimationAsDynamicMontage(ShootAnim, "Action");
	UE_LOG(LogTemp, Warning, TEXT("Played"));
}

void URifleAnim::PlayReloadAnim()
{
	PlaySlotAnimationAsDynamicMontage(ReloadAnim, "Action");
}

void URifleAnim::PlayDeathAnim_Implementation(float Ratio)
{
	
	CurrentDeath = GetRandAnim(DeathAnimations, DeathIndex);
	float Time = CurrentDeath->GetPlayLength();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &URifleAnim::DeathIsFinished, Time, false);
}

void URifleAnim::PlayHitAnim_Implementation()
{
	PlaySlotAnimationAsDynamicMontage(HitAnimation, "Damaged");																
}

UAnimSequence* URifleAnim::GetRandAnim(TArray<UAnimSequence*>& Animations, int& Index)
{
	UAnimSequence* NewAnim;
	while (true)
	{
		srand(time(NULL));
		Index = rand() % Animations.Num() - 1;
		Index = FMath::Clamp(Index, 0, Animations.Num() - 1);
		NewAnim = Animations[Index];
		if (NewAnim != nullptr)
			break;
	}
	return NewAnim;
}

void URifleAnim::DeathIsFinished()
{
	OnDeathFinished.Broadcast();
}

void URifleAnim::PersonaUpdate_Implementation()
{
	PlayShootAnim();

	if (DebugDeath)
	{
		DebugDeath = !DebugDeath;
		PlayDeathAnim(0.f);
	}
	else if (DebugDamaged)
	{
		DebugDamaged = !DebugDamaged;
		PlayHitAnim();
	}
	else if (DebugReload)
	{
		DebugReload = !DebugReload;
		PlayReloadAnim();
	}


}
