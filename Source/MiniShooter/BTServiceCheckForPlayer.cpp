// Fill out your copyright notice in the Description page of Project Settings.

#include "BTServiceCheckForPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoard/BlackboardKeyAllTypes.h"
#include "AIBasicEnemyChar.h"
#include "AIBasicEnemyCtr.h"
#include "MiniShooter.h"

UBTServiceCheckForPlayer::UBTServiceCheckForPlayer()
{
	bCreateNodeInstance = true;
}
void UBTServiceCheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIBasicEnemyCtr *EnemyPC = Cast<AAIBasicEnemyCtr>(OwnerComp.GetAIOwner());

	if (EnemyPC)
	{
		AAIBasicEnemyChar *Enemy = Cast<AAIBasicEnemyChar>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (Enemy)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID, Enemy);
		}
	}
 }

