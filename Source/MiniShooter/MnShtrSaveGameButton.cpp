// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrSaveGameButton.h"
#include "MnShtrMainMenuGameMode.h"
#include "MnShtrGameInstance.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MnShtrSaveGame.h"

UMnShtrSaveGameButton::UMnShtrSaveGameButton()
{
	OnClicked.AddDynamic(this, &UMnShtrSaveGameButton::LoadGameFile);
	saveSlotName = TEXT("TestSaveSlot");
	userIndex = 0;
}

void UMnShtrSaveGameButton::LoadGameFile()
{
	UMnShtrSaveGame* loadGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::CreateSaveGameObject(UMnShtrSaveGame::StaticClass()));
	loadGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::LoadGameFromSlot(saveSlotName, 0));
	UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
	gameInstance->PlayerName = loadGameInstance->PlayerName;
	gameInstance->Level= loadGameInstance->Level;
	gameInstance->Stage = loadGameInstance->Stage;
	gameInstance->CanRun = loadGameInstance->CanRun;
	gameInstance->CanJump = loadGameInstance->CanJump;
	gameInstance->BetterGun = loadGameInstance->BetterGun;
	gameInstance->Exp = loadGameInstance->Exp;
	gameInstance->mustRead = true;
	UGameplayStatics::OpenLevel(world, gameInstance->Level);	
}


