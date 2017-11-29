// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_FirstPerson/FP_FirstPersonGameMode.h"
#include "MnShtrGameModeBase.h"
#include "MnShtrPauseMenuGameMode.generated.h"

/**
*
*/
UCLASS()
class MINISHOOTER_API AMnShtrPauseMenuGameMode : public AMnShtrGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maciek")
		TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maciek")
		TSubclassOf<UUserWidget> SaveMenuClass;

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void ResumeButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void SaveButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void SaveMenuSaveButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void MainMenuButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void QuitButtonClick();

	UFUNCTION(BlueprintCallable, Category = "Maciek")
		void BackButtonClick();

};
