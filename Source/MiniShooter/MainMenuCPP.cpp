// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuCPP.h"
#include "MnShtrGameInstance.h"

void UMainMenuCPP::InitializeContent()
{
	UWorld* world = GetWorld();
	UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
	if (!gameInstance)
	{
		return;
	}
	bool show = gameInstance->mustRead;
	if (show)
	{
		if (SaveButtonCPP)
			SaveButtonCPP->SetVisibility(ESlateVisibility::Visible);
		if (YourProfileButtonCPP)
			YourProfileButtonCPP->SetVisibility(ESlateVisibility::Visible);
		if (GreetingsTextBlockCPP)
		{
			GreetingsTextBlockCPP->SetVisibility(ESlateVisibility::Visible);
			GreetingsTextBlockCPP->SetText(FText::FromString(FString(TEXT("Welcome ")) +gameInstance->PlayerName.ToString()+FString(TEXT("!"))));
		}
	}
	else
	{
		if (SaveButtonCPP)
			SaveButtonCPP->SetVisibility(ESlateVisibility::Collapsed);
		if (YourProfileButtonCPP)
			YourProfileButtonCPP->SetVisibility(ESlateVisibility::Collapsed);
		if (GreetingsTextBlockCPP)
			GreetingsTextBlockCPP->SetVisibility(ESlateVisibility::Collapsed);
	}
}
