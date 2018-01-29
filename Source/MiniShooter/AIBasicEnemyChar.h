// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIBasicEnemyChar.generated.h"

UCLASS()
class MINISHOOTER_API AAIBasicEnemyChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBasicEnemyChar();

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree *BotBehavior;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AAIBullet> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AActor> MissleClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float HitPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float Experiance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float DmgMultiplier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float Energy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float MaxEnergy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float DamageDelt;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
		void GetRekt(float dmg);

	UFUNCTION()
		void FireBasic();

	UFUNCTION()
		void Explode();

	UFUNCTION()
		void FireGranade();

	UFUNCTION()
		void AssignDamageDelt(float dmg);

	UFUNCTION()
		void Heal();

	float GetEnergy();

	float GetHealth();


private:

		void Fire(int BulletType);

};
