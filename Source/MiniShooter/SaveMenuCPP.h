// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "SaveMenuCPP.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API USaveMenuCPP : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void SaveButtonClick();
	UPROPERTY(BlueprintReadWrite, Category = "Maciek")
		UEditableTextBox *SaveGameNameTextBox;
};
