// Fill out your copyright notice in the Description page of Project Settings.
#include "MnShtrMainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"

void AMnShtrMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("MnShtr MAIN MENU GAME MODE.CPP"));
	StartShowingStartingWidget();
}

void AMnShtrMainMenuGameMode::PlayButtonClick()
{
	ChangeMenuWidget(nullptr);
	UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonExampleMap2");
	APlayerController *playerController = GetWorld()->GetFirstPlayerController();
	playerController->SetInputMode(FInputModeGameOnly());
	playerController->bShowMouseCursor = false;
	playerController->SetPause(false);
}

void AMnShtrMainMenuGameMode::LoadButtonClick()
{
	if (LoadMenuClass)
	{
		ChangeMenuWidget(LoadMenuClass);
	}
}

void AMnShtrMainMenuGameMode::LoadMenuLoadButtonClick()
{
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("NOT IMPLEMENTED!!!"));
}

void AMnShtrMainMenuGameMode::OptionsButtonClick()
{
	if (OptionsMenuClass)
	{
		ChangeMenuWidget(OptionsMenuClass);
	}
}

void AMnShtrMainMenuGameMode::QuitButtonClick()
{
	GetWorld()->GetFirstLocalPlayerFromController()->ConsoleCommand("quit");
}

void AMnShtrMainMenuGameMode::BackButtonClick()
{
	if (MainMenuClass)
	{
		ChangeMenuWidget(MainMenuClass);
	}
}
