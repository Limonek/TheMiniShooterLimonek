// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MnShtrGameModeBase.h"
#include "MnShtrMainMenuGameMode.generated.h"

/**
*
*/
UCLASS()
class MINISHOOTER_API AMnShtrMainMenuGameMode : public AMnShtrGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maciek")
		TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maciek")
		TSubclassOf<UUserWidget> LoadMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maciek")
		TSubclassOf<UUserWidget> OptionsMenuClass;

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void PlayButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void LoadButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void LoadMenuLoadButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void OptionsButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void QuitButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void BackButtonClick();
};
