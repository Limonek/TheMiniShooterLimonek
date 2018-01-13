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
	//UMnShtrSaveGame(FText name);

	//UPROPERTY()
	//	uint32 UserIndex;

	//UPROPERTY()
	//	FString SaveSlotName;

	UPROPERTY()
		FText PlayerName;

	UPROPERTY()
		FName Level;

	UPROPERTY()
		FName Stage;

	UPROPERTY()
		bool CanRun;

	UPROPERTY()
		bool CanJump;

	UPROPERTY()
		bool BetterGun;

	UPROPERTY()
		int32 Exp;
};
