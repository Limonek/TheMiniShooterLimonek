// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ProfileWidgetCPP.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UProfileWidgetCPP : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void InitializeContent();

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UButton* RunButtonCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UButton* JumpButtonCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UButton* GunButtonCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UTextBlock* RunTextBoxCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UTextBlock* JumpTextBoxCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UTextBlock* GunTextBoxCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UTextBlock* NameTextBoxCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UTextBlock* ExpTextBoxCPP;

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void BuyRunButtonClickCPP();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void BuyJumpButtonClickCPP();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void BuyGunButtonClickCPP();

};
