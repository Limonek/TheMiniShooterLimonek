// Fill out your copyright notice in the Description page of Project Settings.
#include "AIBasicEnemyChar.h"
#include "AIBullet.h"
#include "MiniCharacter.h"
#include "MiniShooter.h"



// Sets default values
AAIBasicEnemyChar::AAIBasicEnemyChar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitPoints = 100.0f;
	Experiance = 10.0f;
	DmgMultiplier = 1.0f;
	Energy = 100.0f;
	MaxEnergy = Energy;
}

// Called when the game starts or when spawned
void AAIBasicEnemyChar::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAIBasicEnemyChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Energy < MaxEnergy)
		Energy++;

}

// Called to bind functionality to input
void AAIBasicEnemyChar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AAIBasicEnemyChar::GetRekt(float dmg)
{
	HitPoints -= dmg;
	if (HitPoints <= 0) {
		AMiniCharacter *Enemy = Cast<AMiniCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if(Enemy)
			Enemy->GetExp(Experiance);
		Destroy();
	}
}

void AAIBasicEnemyChar::Fire()
{
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation =  GetActorLocation() + FVector(0.2f, 48.4f, -10.6f);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<AAIBullet>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

}

