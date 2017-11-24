// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MnShtrSaveGame.generated.h"

/**
 *
 */
UCLASS()
class MINISHOOTER_API UMnShtrSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UMnShtrSaveGame();
	UMnShtrSaveGame(FText name);

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString palyerName;

	UPROPERTY()
		FString levelName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FVector Location;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FRotator Rotation;
};
