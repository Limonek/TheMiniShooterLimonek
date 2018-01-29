// Fill out your copyright notice in the Description page of Project Settings.

#include "AIBullet.h"
#include "MiniCharacter.h"
#include "AIBasicEnemyChar.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

// Sets default values
AAIBullet::AAIBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &AAIBullet::OnHit);		// set up a notification for when this component hits something blocking
	// Set the root component to be the collision component.
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComponent;

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = CollisionComponent;
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	InitialLifeSpan = 3.0f;
	Damage = 5.0f;
	Explode = false;
}

// Called when the game starts or when spawned
void AAIBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(AMiniCharacter::StaticClass()))
		{
			AMiniCharacter* Pawn(Cast<AMiniCharacter>(OtherActor));
			if (Pawn)
			{
				const FDamageEvent DamageEvent;
				AController* EventInstigator = nullptr;
				AActor* DamageCauser = this;
				Pawn->GetRekt(Damage);
				Shooter->AssignDamageDelt(Damage);
			}
		}
	}
}

void AAIBullet::SetShooter(AAIBasicEnemyChar *shooter, float dmgMultiplier, bool asd) {
	Shooter = shooter;
	Damage = dmgMultiplier;
	Explode = asd;
}