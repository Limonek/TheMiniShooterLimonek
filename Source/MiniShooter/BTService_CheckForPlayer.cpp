// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckForPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoard/BlackboardKeyAllTypes.h"
#include "AIBasicEnemyChar.h"
#include "AIBasicEnemyCtr.h"
#include "MiniShooter.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"


UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}
void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIBasicEnemyCtr *EnemyPC = Cast<AAIBasicEnemyCtr>(OwnerComp.GetAIOwner());

	if (EnemyPC)
	{
		ACharacter *Enemy = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (Enemy)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID, Enemy);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt("Strategy", EnemyPC->EvaluateData());
		}
	}
}

