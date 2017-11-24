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
	ULoadMenuCPP(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Maciek's Category")
		void UpdateSaveGameList();

	UPROPERTY(BlueprintReadWrite, Category = "Maciek's Category")
		UScrollBox* SavedGamesContainer;

	UFUNCTION(BlueprintCallable, Category = "Maciek's Category")
		TArray<FString> ListSavedGameSlots();

	UFUNCTION(BlueprintCallable, Category = "Maciek's Category")
		void OnClick();
};
