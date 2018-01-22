// Fill out your copyright notice in the Description page of Project Settings.
#include "MnShtrMainMenuGameMode.h"
#include "MnShtrGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AMnShtrMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartShowingStartingWidget();
}

void AMnShtrMainMenuGameMode::PlayButtonClick()
{
	UWorld* world = GetWorld();
	UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
	if (gameInstance->mustRead)
	{
		UGameplayStatics::OpenLevel(world, gameInstance->Level);
	}
	else
	{
		if (GiveNameWidgetClass)
		{
			ChangeMenuWidget(GiveNameWidgetClass);
		}
	}
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

void AMnShtrMainMenuGameMode::ShowMainBackButtonClick()
{
	if (MainMenuClass)
	{
		ChangeMenuWidget(MainMenuClass);
	}
}

void AMnShtrMainMenuGameMode::ShowOptionsBackButtonClick()
{
	if (MainMenuClass)
	{
		ChangeMenuWidget(OptionsMenuClass);
	}
}

void AMnShtrMainMenuGameMode::ShowVideoSettingsButtonClick()
{
	if (MainMenuClass)
	{
		ChangeMenuWidget(VideoMenuClass);
	}
}

void AMnShtrMainMenuGameMode::ShowYourProfileButtonClick()
{
	ChangeMenuWidget(ProfileWidgetClass);
}

void AMnShtrMainMenuGameMode::SaveButtonClick()
{
	ChangeMenuWidget(SaveMenuClass);
}
