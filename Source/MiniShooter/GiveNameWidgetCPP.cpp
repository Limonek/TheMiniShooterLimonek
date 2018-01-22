// Fill out your copyright notice in the Description page of Project Settings.

#include "GiveNameWidgetCPP.h"
#include "MnShtrMainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MnShtrGameInstance.h"

void UGiveNameWidgetCPP::ContinueButtonClick()
{
	UWorld *world = GetWorld();
	AMnShtrMainMenuGameMode *gameMode = Cast<AMnShtrMainMenuGameMode>(UGameplayStatics::GetGameMode(world));
	gameMode->ChangeMenuWidget(nullptr);
	UMnShtrGameInstance* mnShtrGameInstance = Cast<UMnShtrGameInstance>(gameMode->GetGameInstance());
	if (!mnShtrGameInstance->mustRead)
	{
		mnShtrGameInstance->InitializeNewPlayerGameInstance(PlayerNameEditableTextBoxCPP->GetText(), gameMode->FirstLevelName);
	}
	UGameplayStatics::OpenLevel(GetWorld(), mnShtrGameInstance->Level);
}