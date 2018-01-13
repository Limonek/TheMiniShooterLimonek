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

	UFUNCTION(BlueprintCallable, Category = Game)
		AActor* ChoosePlayerStart_Implementation(AController* Player);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> SaveMenuClass;

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ResumeButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void SaveButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void SaveMenuSaveButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void MainMenuButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void QuitButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void BackButtonClick();
};
