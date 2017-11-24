// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Button.h"
#include "MnShtrSaveGameButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadDelegate, FString, NazwaPliku);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

/**
 *
 */
UCLASS()
class MINISHOOTER_API UMnShtrSaveGameButton : public UButton
{
	GENERATED_BODY()
public:

	UPROPERTY()
		FString saveSlotName;

	UPROPERTY()
		int userIndex;

	UPROPERTY()
		UWorld *world;

	UMnShtrSaveGameButton(FString name, UWorld *world);
	UMnShtrSaveGameButton();

	UPROPERTY()
		FLoadDelegate load;

	UPROPERTY()
		FClickDelegate click;

	UFUNCTION()
		void OnClick();

	UFUNCTION()
		void LoadGameFile();
};
