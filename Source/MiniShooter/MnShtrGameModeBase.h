// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "FP_FirstPerson/FP_FirstPersonGameMode.h"
#include "MnShtrGameModeBase.generated.h"

/**
*
*/
UCLASS()
class MINISHOOTER_API AMnShtrGameModeBase : public AFP_FirstPersonGameMode
{
	GENERATED_BODY()
public:
	UFUNCTION()
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay()override;

public:
	UPROPERTY()
		UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maciek")
		TSubclassOf<UUserWidget> StartingWidget;

	void StartShowingStartingWidget();
};
