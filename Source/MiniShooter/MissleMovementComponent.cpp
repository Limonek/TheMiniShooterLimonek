// Fill out your copyright notice in the Description page of Project Settings.

#include "MissleMovementComponent.h"
#include "MiniCharacter.h"



void UMissleMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}
	const FVector ActorLocation = GetActorLocation();
	AMiniCharacter *Enemy = Cast<AMiniCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (Enemy != NULL)
	{
		FVector Direction = Enemy->GetActorLocation() - ActorLocation;
		FRotator NewControlRotation = Direction.Rotation();
		FVector DesiredMovementThisFrame = NewControlRotation.RotateVector(ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f);

		// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick

		if (!DesiredMovementThisFrame.IsNearlyZero())
		{
			FHitResult Hit;
			SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		}
	}
};