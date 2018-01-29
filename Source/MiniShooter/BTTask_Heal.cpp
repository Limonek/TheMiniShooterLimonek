// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Heal.h"
#include "MiniShooter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoard/BlackboardKeyAllTypes.h"
#include "AIBasicEnemyChar.h"
#include "AIBasicEnemyCtr.h"

#define FIRE 1
#define GRANADE 2
#define HEAL 3
#define EXPLODE 4

EBTNodeResult::Type UBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIBasicEnemyCtr *CharPc = Cast<AAIBasicEnemyCtr>(OwnerComp.GetAIOwner());

	ACharacter *Enemy = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPc->EnemyKeyID));

	if (Enemy && OwnerComp.GetBlackboardComponent()->GetValueAsInt("Strategy") == HEAL)
	{
		AAIBasicEnemyChar *Bot = Cast<AAIBasicEnemyChar>(CharPc->GetCharacter());
		Bot->Heal();
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	EBTNodeResult::Failed;
}


