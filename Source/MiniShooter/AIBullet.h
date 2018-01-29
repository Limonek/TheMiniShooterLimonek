// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Actor.h"
#include "AIBullet.generated.h"

UCLASS(config = Game)
class MINISHOOTER_API AAIBullet : public AActor
{
	GENERATED_BODY()

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class	USphereComponent* CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class	UProjectileMovementComponent* ProjectileMovementComponent;
	
public:	
	// Sets default values for this actor's properties
	AAIBullet();

	AAIBasicEnemyChar *Shooter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns CollisionComp subobject **/
	class USphereComponent* GetCollisionComp() const { return CollisionComponent; }
	/** Returns ProjectileMovement subobject **/
	class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovementComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		bool Explode;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void SetShooter(AAIBasicEnemyChar *Shooter, float DmgMultiplier, bool asd);

	
};
