// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadMenuCPP.h"
#include "MnShtrSaveGameButton.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/ButtonSlot.h"
#include "Components/Button.h"

ULoadMenuCPP::ULoadMenuCPP(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("CPP Constructor"));
}

void ULoadMenuCPP::UpdateSaveGameList()
{
	if (!SavedGamesContainer)
	{
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ScrollBox is not set!"));
		return;
	}
	UMnShtrSaveGameButton *button;
	UTextBlock *text;
	UPanelSlot*slot;
	UScrollBoxSlot *scrollBoxSlot;
	UButtonSlot*buttonSlot;
	TArray<FString> SaveGames = ListSavedGameSlots();

	for (auto& Str : SaveGames)
	{
		text = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		text->SetText(FText::FromString(Str));
		button = NewObject<UMnShtrSaveGameButton>(this, UMnShtrSaveGameButton::StaticClass());
		button->saveSlotName = Str;
		button->world = GetWorld();
		//(button->OnClicked).AddDynamic(this, &ULoadMenuCPP::OnClick);
		slot = button->AddChild(text);
		buttonSlot = Cast<UButtonSlot>(slot);
		buttonSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Left;
		button->SetBackgroundColor(FLinearColor(.0f, .0f, .0f, .0f));
		slot = SavedGamesContainer->AddChild(button);
		scrollBoxSlot = Cast<UScrollBoxSlot>(slot);
		scrollBoxSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Left;
	}
}

void ULoadMenuCPP::OnClick()
{
	//UMnShtrSaveGame* LoadGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::CreateSaveGameObject(UMnShtrSaveGame::StaticClass()));
	//LoadGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	//this->SetActorLocation(LoadGameInstance->Location);
	//GetController()->SetControlRotation(LoadGameInstance->Rotation);
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Game loaded"));
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("LoadMenuCPP Button Click! :)"));
}


TArray<FString> ULoadMenuCPP::ListSavedGameSlots()
{

	TArray<FString> FileNames;
	TArray<FString> FileNamesWithoutExtensions;
	FFileManagerGeneric FileMgr;
	FileMgr.SetSandboxEnabled(true);// don't ask why, I don't know :P
	FString wildcard("*"); // May be "" (empty string) to search all files
	FString search_path(FPaths::Combine(*FPaths::GameSavedDir(), TEXT("SaveGames"), *wildcard));

	FileMgr.FindFiles(FileNames, *search_path,
		true,  // to list files
		true); // to skip directories

	FString extension = FString(TEXT(".sav"));
	for (auto f : FileNames)
	{
		f.RemoveFromEnd(extension);
		FileNamesWithoutExtensions.Add(f);
	}

	return FileNamesWithoutExtensions;
}

