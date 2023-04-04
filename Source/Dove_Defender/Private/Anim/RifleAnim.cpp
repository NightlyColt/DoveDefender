// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/RifleAnim.h"

void URifleAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (nullptr != Pawn) {
		auto Velocity = Pawn->GetVelocity();
		Speed = Velocity.Size();
		auto Rotation = Pawn->GetActorRotation();
		Direction = CalculateDirection(Velocity, Rotation);
	}
}