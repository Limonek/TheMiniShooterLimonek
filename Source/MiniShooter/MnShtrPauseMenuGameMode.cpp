// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrPauseMenuGameMode.h"
#include "Kismet/GameplayStatics.h"

void AMnShtrPauseMenuGameMode::ResumeButtonClick()
{
	ChangeMenuWidget(nullptr);
	APlayerController *playerController = GetWorld()->GetFirstPlayerController();
	playerController->SetInputMode(FInputModeGameOnly());
	playerController->bShowMouseCursor = false;
	playerController->SetPause(false);
}

void AMnShtrPauseMenuGameMode::SaveButtonClick()
{
	ChangeMenuWidget(SaveMenuClass);
}

void AMnShtrPauseMenuGameMode::SaveMenuSaveButtonClick()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("NOT IMPLEMENTED!!!"));
}

void AMnShtrPauseMenuGameMode::MainMenuButtonClick()
{
	ChangeMenuWidget(nullptr);
	UGameplayStatics::OpenLevel(GetWorld(), "StartLevel");
}

void AMnShtrPauseMenuGameMode::BackButtonClick()
{
	ChangeMenuWidget(PauseMenuClass);
}

void AMnShtrPauseMenuGameMode::QuitButtonClick()
{
	GetWorld()->GetFirstLocalPlayerFromController()->ConsoleCommand("quit");
}
