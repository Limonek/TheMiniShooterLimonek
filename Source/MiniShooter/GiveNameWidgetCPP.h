// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "GiveNameWidgetCPP.generated.h"

/**
 *
 */
UCLASS()
class MINISHOOTER_API UGiveNameWidgetCPP : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ContinueButtonClick();

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UEditableTextBox* PlayerNameEditableTextBoxCPP;

};