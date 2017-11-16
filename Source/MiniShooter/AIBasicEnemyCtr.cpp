// Fill out your copyright notice in the Description page of Project Settings.
#include "AIBasicEnemyCtr.h"
#include "MiniShooter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoard/BlackboardKeyAllTypes.h"
#include "AIBasicEnemyChar.h"
#include "AIBasicEnemyCtr.h"
AAIBasicEnemyCtr::AAIBasicEnemyCtr()
{
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	BehaviourComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
}

void AAIBasicEnemyCtr::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	AAIBasicEnemyChar *Char = Cast<AAIBasicEnemyChar>(InPawn);

	if (Char && Char->BotBehavior)
	{
		BlackBoardComp->InitializeBlackboard(*Char->BotBehavior->BlackboardAsset);

		EnemyKeyID = BlackBoardComp->GetKeyID("Target");

		BehaviourComp->StartTree(*Char->BotBehavior);
	}
}
