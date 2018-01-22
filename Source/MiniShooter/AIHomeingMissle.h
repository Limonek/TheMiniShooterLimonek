// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Actor.h"
#include "AIHomeingMissle.generated.h"

UCLASS()
class MINISHOOTER_API AAIHomeingMissle : public AActor
{
	GENERATED_BODY()

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class	USphereComponent* CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class	UMissleMovementComponent* ProjectileMovementComponent;

public:
	// Sets default values for this actor's properties
	AAIHomeingMissle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns CollisionComp subobject **/
	class USphereComponent* GetCollisionComp() const { return CollisionComponent; }
	/** Returns ProjectileMovement subobject **/
	class UMissleMovementComponent* GetProjectileMovement() const { return ProjectileMovementComponent; }

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
