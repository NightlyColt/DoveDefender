// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/RifleAnim.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimSequence.h"

URifleAnim::URifleAnim()
{
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
		PersonaUpdates();
}

void URifleAnim::OnActionComplete()
{
	OnActionCompleteD.Broadcast();
}

void URifleAnim::PlayShootAnim()
{
	PlaySlotAnimationAsDynamicMontage(ShootAnim, "Action");

}

void URifleAnim::PlayReloadAnim()
{
	PlaySlotAnimationAsDynamicMontage(ReloadAnim, "Action");
}

void URifleAnim::PlayDeathAnim(float Ratio)
{

	CurrentDeath = GetRandAnim(DeathAnimations, DeathIndex);
	float Time = CurrentDeath->GetPlayLength();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &URifleAnim::DeathIsFinished, Time, false);
}

void URifleAnim::PlayHitAnim()
{
	int Index;
	HitAnimation = GetRandAnim(HitAnimations, Index);
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

void URifleAnim::PersonaUpdates()
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
