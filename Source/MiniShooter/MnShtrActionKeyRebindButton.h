// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MnShtrKeyRebindButton.h"
#include "MnShtrActionKeyRebindButton.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UMnShtrActionKeyRebindButton : public UMnShtrKeyRebindButton
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnClick() override;
	UPROPERTY()
		FInputActionKeyMapping ActionMapping;
	
};
