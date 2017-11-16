// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTaskMoveToPlayer.h"
#include "MiniShooter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoard/BlackboardKeyAllTypes.h"
#include "AIBasicEnemyChar.h"
#include "AIBasicEnemyCtr.h"





EBTNodeResult::Type UBTTaskMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIBasicEnemyCtr *CharPc = Cast<AAIBasicEnemyCtr>(OwnerComp.GetAIOwner());

	AAIBasicEnemyChar *Enemy = Cast<AAIBasicEnemyChar>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPc->EnemyKeyID));

	if (Enemy)
	{
		CharPc->MoveToActor(Enemy, 5.f, true, true, true, 0, true);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	EBTNodeResult::Failed;
}