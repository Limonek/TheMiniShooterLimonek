// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadMenuCPP.h"
#include "MnShtrSaveGameButton.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/ButtonSlot.h"
#include "Components/Button.h"

void ULoadMenuCPP::UpdateSaveGameList()
{
	if (!SavedGamesContainer)
	{
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
		slot = button->AddChild(text);
		buttonSlot = Cast<UButtonSlot>(slot);
		buttonSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Left;
		button->SetBackgroundColor(FLinearColor(.0f, .0f, .0f, .0f));
		slot = SavedGamesContainer->AddChild(button);
		scrollBoxSlot = Cast<UScrollBoxSlot>(slot);
		scrollBoxSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Left;
	}
}

TArray<FString> ULoadMenuCPP::ListSavedGameSlots()
{
	TArray<FString> FileNames;
	TArray<FString> FileNamesWithoutExtensions;
	FFileManagerGeneric FileMgr;
	FileMgr.SetSandboxEnabled(true);
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

