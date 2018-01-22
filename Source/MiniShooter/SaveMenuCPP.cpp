// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveMenuCPP.h"
#include "MnShtrSaveGame.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "MnShtrGameInstance.h"
#include "Kismet/GameplayStatics.h"


//MnShtr function
void USaveMenuCPP::SaveButtonClick()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("SaveMenuCPP Click"));
	UMnShtrSaveGame* SaveGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::CreateSaveGameObject(UMnShtrSaveGame::StaticClass()));
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (SaveGameNameTextBox && SaveGameNameTextBox->GetText().ToString().Len() != 0)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Game Saved"));
		UWorld* world = GetWorld();
		UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
		SaveGameInstance->PlayerName = gameInstance->PlayerName;
		SaveGameInstance->Level = gameInstance->Level;
		SaveGameInstance->Stage = gameInstance->Stage;
		SaveGameInstance->CanRun = gameInstance->CanRun;
		SaveGameInstance->CanJump = gameInstance->CanJump;
		SaveGameInstance->BetterGun = gameInstance->BetterGun;
		SaveGameInstance->Exp = gameInstance->Exp;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameNameTextBox->GetText().ToString(), 0);
	}
}


