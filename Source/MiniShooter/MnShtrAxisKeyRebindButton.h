// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MnShtrKeyRebindButton.h"
#include "MnShtrAxisKeyRebindButton.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UMnShtrAxisKeyRebindButton : public UMnShtrKeyRebindButton
{
	GENERATED_BODY()
public:
	UFUNCTION()
		void OnClick() override;
	UPROPERTY()
		FInputAxisKeyMapping AxisMapping;			
	
};
