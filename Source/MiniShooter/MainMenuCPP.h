// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MainMenuCPP.generated.h"

/**
 *
 */
UCLASS()
class MINISHOOTER_API UMainMenuCPP : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="MnShtr")
		void InitializeContent();

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UButton* YourProfileButtonCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UButton* SaveButtonCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UTextBlock* GreetingsTextBlockCPP;

};
