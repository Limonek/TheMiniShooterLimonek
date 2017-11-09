// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FP_FirstPersonGameMode.generated.h"

using namespace UP;

UCLASS(minimalapi)
class AFP_FirstPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFP_FirstPersonGameMode();

	UFUNCTION()
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay()override;

public:
	UPROPERTY()
		UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Maciek")
		TSubclassOf<UUserWidget> StartingWidget;

	void StartShowingStartingWidget();
};



