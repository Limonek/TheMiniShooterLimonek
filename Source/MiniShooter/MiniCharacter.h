// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Character.h"
#include "MiniCharacter.generated.h"

UCLASS()
class MINISHOOTER_API AMiniCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMiniCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float HitPoints;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float Experiance;

	UFUNCTION()
		void GetRekt(float dmg);

	UFUNCTION()
		void GetExp(float dmg);
};
