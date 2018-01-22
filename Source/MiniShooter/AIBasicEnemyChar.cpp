// Fill out your copyright notice in the Description page of Project Settings.
#include "AIBasicEnemyChar.h"
#include "AIBullet.h"
#include "MiniCharacter.h"
#include "MiniShooter.h"

#define BASICBULLET 1

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
		if (Enemy)
			Enemy->GetExp(Experiance);
		Destroy();
	}
}

void AAIBasicEnemyChar::FireBasic()
{
	Fire(BASICBULLET);
}

void AAIBasicEnemyChar::Fire(int BulletType)
{
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector ActorLocation = GetActorLocation();// +FVector(0.2f, 10.4f, -10.6f);

			AMiniCharacter *Enemy = Cast<AMiniCharacter>(World->GetFirstPlayerController()->GetCharacter());
			if (Enemy != NULL) {
				const FVector EnemyLocation = Enemy->GetActorLocation();

				FVector Direction = EnemyLocation - GetActorLocation();
				FRotator NewControlRotation = Direction.Rotation();
				const FVector SpawnLocation = ActorLocation + SpawnRotation.RotateVector(FVector(30.2f, 10.4f, 30.6f));
				NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);
				FaceRotation(NewControlRotation, 0.2f);


				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				switch (BulletType) {
				case BASICBULLET:
					World->SpawnActor<AAIBullet>(MissleClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					break;

				}


			}
		}
	}

}

void AAIBasicEnemyChar::FireAll()
{
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetActorLocation() + FVector(0.2f, 10.4f, -10.6f);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AAIBullet>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

}


void AAIBasicEnemyChar::Explode()
{

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			AMiniCharacter *Enemy = Cast<AMiniCharacter>(World->GetFirstPlayerController()->GetCharacter());
			if (Enemy != NULL) {
				const FVector ActorLocation = GetActorLocation();
				const FVector EnemyLocation = Enemy->GetActorLocation();
				if ((ActorLocation - EnemyLocation).Size() < 1000)
				{
					Enemy->GetRekt(20);
					Destroy();
				}
			}
		}

}

