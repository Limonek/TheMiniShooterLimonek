// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"
#include "ScrollBox.h"
#include "Blueprint/UserWidget.h"
#include "LoadMenuCPP.generated.h"
/**
 *
 */
UCLASS()
class MINISHOOTER_API ULoadMenuCPP : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void UpdateSaveGameList();

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UScrollBox* SavedGamesContainer;

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		TArray<FString> ListSavedGameSlots();
};
