// Fill out your copyright notice in the Description page of Project Settings.
#include "AIBasicEnemyChar.h"
#include "AIBullet.h"
#include "MiniCharacter.h"
#include "AIBasicEnemyCtr.h"
#include "MiniShooter.h"

#define BASICBULLET 1
#define GRANADE 2

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
	DamageDelt = 0;
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
			Enemy->AddExp(Experiance);
		Cast<AAIBasicEnemyCtr>(GetController())->SaveData(DamageDelt);
		Destroy();
	}
}

void AAIBasicEnemyChar::FireBasic()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, TEXT("Fire"));
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
				AAIBullet *Bullet = World->SpawnActor<AAIBullet>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				switch (BulletType) {
				case BASICBULLET:
					if(Bullet)
					Bullet->SetShooter(this, 5, false);
					break;
				case GRANADE:
					if (Bullet)
					Bullet->SetShooter(this, 20, true);
					break;
				}


			}
		}
	}

}

void AAIBasicEnemyChar::FireGranade()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, TEXT("Granade"));
	if (Energy > 20) {
		Fire(GRANADE);
		Energy -= 20;
	}
}


void AAIBasicEnemyChar::Explode()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, TEXT("Explode"));
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			AMiniCharacter *Enemy = Cast<AMiniCharacter>(World->GetFirstPlayerController()->GetCharacter());
			if (Enemy != NULL) {
				const FVector ActorLocation = GetActorLocation();
				const FVector EnemyLocation = Enemy->GetActorLocation();
				if ((ActorLocation - EnemyLocation).Size() < 100)
				{
					Enemy->GetRekt(20);
					AssignDamageDelt(20);
					Destroy();
				}
			}
		}

}

void AAIBasicEnemyChar::AssignDamageDelt(float dmg)
{
	
	DamageDelt += dmg;
}

void AAIBasicEnemyChar::Heal()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, TEXT("Heal"));
	if (Energy > 2) {
		HitPoints += 1;
		Energy -= 2;
	}
}

float AAIBasicEnemyChar::GetEnergy()
{
	return Energy;
}
float AAIBasicEnemyChar::GetHealth()
{
	return HitPoints;
}