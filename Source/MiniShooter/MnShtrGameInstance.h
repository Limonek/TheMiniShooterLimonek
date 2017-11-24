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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGameInfo")
		FVector location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGameInfo")
		FRotator rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGameInfo")
		bool mustRead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGameInfo")
		FString playerName;




};
