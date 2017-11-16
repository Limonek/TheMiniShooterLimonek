// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveMenuCPP.h"
#include "MnShtrSaveGame.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


//MnShtr function
void USaveMenuCPP::SaveButtonClick()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("SaveMenuCPP Click"));
	UMnShtrSaveGame* SaveGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::CreateSaveGameObject(UMnShtrSaveGame::StaticClass()));
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	SaveGameInstance->Location = playerController->GetCharacter()->GetActorLocation();
	SaveGameInstance->levelName = GetWorld()->GetMapName();
	SaveGameInstance->Rotation = playerController->GetControlRotation();
	if (SaveGameNameTextBox)
		SaveGameInstance->SaveSlotName = SaveGameNameTextBox->GetText().ToString();
	if (SaveGameInstance->SaveSlotName.Len() == 0)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("SaveSlotName.Len()==0"));
	}
	else
	{
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Game Saved"));
	}
}


