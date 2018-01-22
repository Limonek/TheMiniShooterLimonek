// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniCharacter.h"


// Sets default values
AMiniCharacter::AMiniCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitPoints = 100;
	Experiance = 0;
}

// Called when the game starts or when spawned
void AMiniCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMiniCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMiniCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMiniCharacter::GetRekt(float dmg)
{
	HitPoints -= dmg;
	if (HitPoints <= 0) {
		//zabijanie gracza
	}
}

void AMiniCharacter::GetExp(float xp)
{
	Experiance += xp;
}