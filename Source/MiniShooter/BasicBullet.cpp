// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicBullet.h"
#include "AIBasicEnemyChar.h"

// Sets default values
ABasicBullet::ABasicBullet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnActorHit.AddDynamic(this, &ABasicBullet::OnHit);
}

// Called when the game starts or when spawned
void ABasicBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicBullet::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(AAIBasicEnemyChar::StaticClass()))
		{
			AAIBasicEnemyChar* Pawn(Cast<AAIBasicEnemyChar>(OtherActor));
			if (Pawn)
			{
				float DamageAmount = 600.0f;
				const FDamageEvent DamageEvent;
				AController* EventInstigator = nullptr;
				AActor* DamageCauser = this;
				Pawn->GetRekt(DamageAmount);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
			}
		}
	}
}