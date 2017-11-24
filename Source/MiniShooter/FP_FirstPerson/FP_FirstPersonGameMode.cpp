// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FP_FirstPersonGameMode.h"
#include "FP_FirstPersonHUD.h"
#include "MnShtrGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "FP_FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFP_FirstPersonGameMode::AFP_FirstPersonGameMode()
{
	// Set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// Use our custom HUD class
	HUDClass = AFP_FirstPersonHUD::StaticClass();
}

void AFP_FirstPersonGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AFP_FirstPersonGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("FP_FIRST PERSON GAME MODE.CPP"));
	//MnShtr	
	UGameInstance* gameInstance = GetGameInstance();

	if (gameInstance)
	{
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, TEXT("gameInstance!=nullptr"));
		UMnShtrGameInstance* mnShtrGameInstance = Cast<UMnShtrGameInstance>(GetGameInstance());
		if (mnShtrGameInstance->mustRead)
		{
			UWorld *world = GetWorld();
			ACharacter* player = UGameplayStatics::GetPlayerCharacter(world, 0);
			APlayerController *playerController = world->GetFirstPlayerController();
			playerController->SetInputMode(FInputModeGameOnly());
			playerController->bShowMouseCursor = false;
			playerController->SetPause(false);
			player->GetController()->SetControlRotation(mnShtrGameInstance->rotation);
			player->GetController()->GetPawn()->SetActorLocation(mnShtrGameInstance->location);
			//playerController->SetActorLocation(LoadGameInstance->Location);
		}
		//playerController->SetControlRotation(LoadGameInstance->Rotation);
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, LoadGameInstance->Rotation.ToString());
		//playerController->SetActorLocation(LoadGameInstance->Location);
		//playerController->SetActorLocation(LoadGameInstance->Location);
		// GetController()->SetControlRotation(LoadGameInstance->Rotation);
		//ChangeMenuWidget(nullptr);
	}
	else
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, TEXT("gameInstance==nullptr"));
	//end of MnShtr
}

void AFP_FirstPersonGameMode::StartShowingStartingWidget()
{
	ChangeMenuWidget(StartingWidget);
	APlayerController *playerController = GetWorld()->GetFirstPlayerController();
	playerController->SetInputMode(FInputModeGameAndUI());
	playerController->bShowMouseCursor = true;
	playerController->SetPause(true);
}