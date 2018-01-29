// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "StrategyModel.h"
#include "AIBasicEnemyCtr.generated.h"

/**
*
*/
UCLASS()
class MINISHOOTER_API AAIBasicEnemyCtr : public AAIController
{
	GENERATED_BODY()

		UPROPERTY(transient)
		class UBlackboardComponent *BlackBoardComp;

	UPROPERTY(transient)
		class UBehaviorTreeComponent *BehaviourComp;

public:

	AAIBasicEnemyCtr();

	virtual void Possess(APawn *InPawn) override;

	uint8 EnemyKeyID;

	UFUNCTION()
		void SaveData(float Dmg);

	UFUNCTION()
		int EvaluateData();

	UFUNCTION()
		void LoadData();

private:
	AAIBasicEnemyChar *Bot;

	StrategyModel Strategy;

	int GetStrategy(float dist, float energy, float hp);
};
