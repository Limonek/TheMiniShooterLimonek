// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrSaveGameButton.h"
#include "MnShtrMainMenuGameMode.h"
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
	//AMnShtrMainMenuGameMode* gameMode = Cast<AMnShtrMainMenuGameMode>(GetWorld()->GetAuthGameMode());
	//if (gameMode) gameMode->ChangeMenuWidget(nullptr);

	UGameplayStatics::OpenLevel(world, "FirstPersonExampleMap2");
	
	APlayerController *playerController = world->GetFirstPlayerController();
	playerController->SetInputMode(FInputModeGameOnly());
	playerController->bShowMouseCursor = false;
	playerController->SetPause(false);

	playerController->SetControlRotation(LoadGameInstance->Rotation);
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, LoadGameInstance->Rotation.ToString());
	//playerController->SetActorLocation(LoadGameInstance->Location);
	//playerController->SetActorLocation(LoadGameInstance->Location);
	//playerController->SetActorLocation(LoadGameInstance->Location);
	// GetController()->SetControlRotation(LoadGameInstance->Rotation);

	//ChangeMenuWidget(nullptr);
	//UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonExampleMap");
	//APlayerController *playerController = GetWorld()->GetFirstPlayerController();
	//playerController->SetInputMode(FInputModeGameOnly());
	//playerController->bShowMouseCursor = false;
	//playerController->SetPause(false);
}


