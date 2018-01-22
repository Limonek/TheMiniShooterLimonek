// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Character.h"
#include "FP_FirstPerson/MnShtrFirstPersonCharacter.h"
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

	UFUNCTION()
		void GetRekt(float dmg);

	UFUNCTION()
		void AddExp(float dmg);

	//from MnShtrPersonCharacter
public:
	UPROPERTY()
		int32 Exp;
	FTimerHandle DeadTimerHandle;
	UFUNCTION(BlueprintCallable, Category = MnShtr)
		void CountdownFinished();
	//AMnShtrFirstPersonCharacter();
	//jumping
	UFUNCTION()
		void OnStartJump();
	UFUNCTION()
		void OnStopJump();

	virtual void FellOutOfWorld(const UDamageType & dmgType)override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> DeadWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
		int32 MaxJumpCount;
	UPROPERTY()
		int32 CurrentJumpCount;
	UFUNCTION(BlueprintCallable, Category = "Pawn|Character")
		virtual void Landed(const FHitResult& Hit) override;
protected:
	UFUNCTION(BlueprintCallable, Category = "Pawn|Character")
		bool CanJumpInternal_Implementation() const override;
	//jumping end
//protected:
	// APawn interface
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
private:
	void ShowPauseMenu();
	//void LoadGame();
	void StartRun();
	void StopRun();
	//void SaveGame();
	float WalkSpeed = 600;
	float RunSpeed = 1000;

	//end of MnShtrFirstPersonCharacter

};
