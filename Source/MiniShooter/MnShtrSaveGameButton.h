// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Button.h"
#include "MnShtrSaveGameButton.generated.h"

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

	UMnShtrSaveGameButton();

	UFUNCTION()
		void LoadGameFile();
};
