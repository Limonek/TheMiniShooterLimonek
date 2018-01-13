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

	UPROPERTY(EditAnywhere, Category = "MnShtr")
		FName FirstLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> LoadMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> ProfileWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> GiveNameWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> OptionsMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> VideoMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MnShtr")
		TSubclassOf<UUserWidget> SaveMenuClass;

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void PlayButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void LoadButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void LoadMenuLoadButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void OptionsButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void QuitButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ShowMainBackButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ShowOptionsBackButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ShowVideoSettingsButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ShowYourProfileButtonClick();

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void SaveButtonClick();

};
