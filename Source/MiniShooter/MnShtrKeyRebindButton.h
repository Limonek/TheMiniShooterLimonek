// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsMenuCPP.h"
#include "Components/Button.h"
#include "GameFramework/PlayerInput.h"
#include "MnShtrKeyRebindButton.generated.h"

/**
 * 
 */
UCLASS(abstract)
class MINISHOOTER_API UMnShtrKeyRebindButton : public UButton
{
	GENERATED_BODY()
public:
	UMnShtrKeyRebindButton();

	UPROPERTY()
		UOptionsMenuCPP* optionsWidget;
	UFUNCTION()
		virtual void OnClick() PURE_VIRTUAL(CanRedo, );
	UFUNCTION()
		void SetWaitingText();
	UFUNCTION()
		void DisableButton();			
	
};
