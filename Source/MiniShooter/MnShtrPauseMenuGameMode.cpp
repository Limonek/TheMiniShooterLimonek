// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrPauseMenuGameMode.h"
#include "MnShtrGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Public/EngineUtils.h"
#include "GameFramework/PlayerStart.h"

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

AActor* AMnShtrPauseMenuGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, TEXT("My custom choose player start"));
	FString playerStartTag = FString(TEXT("MaciekPlayer"));
	APlayerStart* playerStart = nullptr;
	UWorld* world = GetWorld();
	UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());

	if (UWorld *world = GetWorld())
	{
		for (TActorIterator<APlayerStart> It(world); It; ++It)
		{
			playerStart = *It;
			if (playerStart->PlayerStartTag.Compare(gameInstance->Stage) == 0)
			{
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, playerStartTag+"=="+(playerStart->PlayerStartTag.ToString()));
				playerStart = *It;
				break;
			}
			else
			{
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, playerStartTag + "!=" + (playerStart->PlayerStartTag.ToString()));
			}
		}
	}
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, "chosen player start: " + playerStart->PlayerStartTag.ToString());
	return playerStart;
}
