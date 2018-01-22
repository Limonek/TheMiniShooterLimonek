// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrGameModeBase.h"
#include "MnShtrGameInstance.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
void AMnShtrGameModeBase::StartShowingStartingWidget()
{
	ChangeMenuWidget(StartingWidget);
	APlayerController *playerController = GetWorld()->GetFirstPlayerController();
	playerController->SetInputMode(FInputModeUIOnly());
	playerController->bShowMouseCursor = true;
	playerController->SetPause(true);
}
void AMnShtrGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
void AMnShtrGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UGameInstance* gameInstance = GetGameInstance();

	if (gameInstance)
	{
		UMnShtrGameInstance* mnShtrGameInstance = Cast<UMnShtrGameInstance>(GetGameInstance());
		if (mnShtrGameInstance->mustRead)
		{
			UWorld *world = GetWorld();
			ACharacter* player = UGameplayStatics::GetPlayerCharacter(world, 0);
			APlayerController *playerController = world->GetFirstPlayerController();
			playerController->SetInputMode(FInputModeGameOnly());
			playerController->bShowMouseCursor = false;
			playerController->SetPause(false);
		}
	}
}


