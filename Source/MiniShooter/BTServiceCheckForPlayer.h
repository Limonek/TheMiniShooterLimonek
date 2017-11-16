// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceCheckForPlayer.generated.h"

/**
 * TODO cos jest nie tak ze wstawianiem tego do BT
 */
UCLASS()
class MINISHOOTER_API UBTServiceCheckForPlayer : public UBTService
{
	GENERATED_BODY()
	
public:

	UBTServiceCheckForPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) override;
	
	
};
