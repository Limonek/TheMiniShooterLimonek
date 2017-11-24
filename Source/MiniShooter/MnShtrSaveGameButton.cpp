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
	//Bind function
	//load.AddDynamic(this, &UMnShtrSaveGameButton::LoadGameFile);
}

UMnShtrSaveGameButton::UMnShtrSaveGameButton(FString name, UWorld* _world)
{
	saveSlotName = name;
	userIndex = 0;
	world = _world;
}

void UMnShtrSaveGameButton::OnClick()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("My Save Game Button OnClick"));
	LoadGameFile();
}

void UMnShtrSaveGameButton::LoadGameFile()
{
	UMnShtrSaveGame* LoadGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::CreateSaveGameObject(UMnShtrSaveGame::StaticClass()));
	LoadGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::LoadGameFromSlot(saveSlotName, LoadGameInstance->UserIndex));

	UGameplayStatics::OpenLevel(world, "FirstPersonExampleMap2");
	UMnShtrGameInstance* gameInstance=Cast<UMnShtrGameInstance>( world->GetGameInstance());
	gameInstance->mustRead = true;
	gameInstance->location = LoadGameInstance->Location;
	gameInstance->rotation = LoadGameInstance->Rotation;
	//gameInstance->playerName = LoadGameInstance->playerName;

	//ACharacter* player = UGameplayStatics::GetPlayerCharacter(world, 0);
	//APlayerController *playerController = world->GetFirstPlayerController();
	//playerController->SetInputMode(FInputModeGameOnly());
	//playerController->bShowMouseCursor = false;
	//playerController->SetPause(false);
	//if (player)
	//{
	//	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, player->GetController()->GetControlRotation().ToString());
	//	player->GetController()->SetControlRotation(LoadGameInstance->Rotation);
	//	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, player->GetController()->GetControlRotation().ToString());
	//}
	//playerController->SetControlRotation(LoadGameInstance->Rotation);
	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, LoadGameInstance->Rotation.ToString());
	//playerController->SetActorLocation(LoadGameInstance->Location);
	// GetController()->SetControlRotation(LoadGameInstance->Rotation);
	//ChangeMenuWidget(nullptr);
	//UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonExampleMap");
	//APlayerController *playerController = GetWorld()->GetFirstPlayerController();
	//playerController->SetInputMode(FInputModeGameOnly());
	//playerController->bShowMouseCursor = false;
	//playerController->SetPause(false);
}


