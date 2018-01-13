// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MnShtrGameInstance.generated.h"

/**
 *
 */
UCLASS()
class MINISHOOTER_API UMnShtrGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMnShtrGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
		void InitializeNewPlayerGameInstance(FText PlayerName, FName FirstLevel);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MnShtr|SaveGameInfo")
		FText PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MnShtr|SaveGameInfo")
		FName Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MnShtr|SaveGameInfo")
		FName Stage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MnShtr|SaveGameInfo")
		bool CanRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MnShtr|SaveGameInfo")
		bool CanJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MnShtr|SaveGameInfo")
		bool BetterGun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MnShtr|SaveGameInfo")
		int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MnShtr|SaveGameInfo")
		bool mustRead;
};
