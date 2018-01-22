// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MoveToPlayer.h"
#include "MiniShooter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoard/BlackboardKeyAllTypes.h"
#include "AIBasicEnemyChar.h"
#include "AIBasicEnemyCtr.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIBasicEnemyCtr *CharPc = Cast<AAIBasicEnemyCtr>(OwnerComp.GetAIOwner());

	ACharacter *Enemy = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPc->EnemyKeyID));

	if (Enemy)
	{
		CharPc->MoveToActor(Enemy, 5.f, true, true, true, 0, true);
		AAIBasicEnemyChar *Bot =  Cast<AAIBasicEnemyChar>(CharPc->GetCharacter());
		Bot->Fire();
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	EBTNodeResult::Failed;
}

