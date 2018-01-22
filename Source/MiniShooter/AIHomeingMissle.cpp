// Fill out your copyright notice in the Description page of Project Settings.

#include "AIHomeingMissle.h"
#include "MiniCharacter.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "MissleMovementComponent.h"


// Sets default values
AAIHomeingMissle::AAIHomeingMissle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &AAIHomeingMissle::OnHit);		// set up a notification for when this component hits something blocking
																				// Set the root component to be the collision component.
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComponent;

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UMissleMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = CollisionComponent;
	InitialLifeSpan = 8.0f;
}

// Called when the game starts or when spawned
void AAIHomeingMissle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIHomeingMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAIHomeingMissle::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(AMiniCharacter::StaticClass()))
		{
			AMiniCharacter* Pawn(Cast<AMiniCharacter>(OtherActor));
			if (Pawn)
			{
				float DamageAmount = 1.0f;
				const FDamageEvent DamageEvent;
				AController* EventInstigator = nullptr;
				AActor* DamageCauser = this;
				Pawn->GetRekt(DamageAmount);
			}
		}
	}
}