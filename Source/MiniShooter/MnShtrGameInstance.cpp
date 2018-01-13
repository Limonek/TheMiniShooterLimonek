// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrGameInstance.h"

UMnShtrGameInstance::UMnShtrGameInstance(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	mustRead = false;
}

void UMnShtrGameInstance::InitializeNewPlayerGameInstance(FText PlayerName, FName FirstLevel)
{
	this->PlayerName = PlayerName;
	Level = FirstLevel;
	Stage = "1";
	CanRun = false;
	CanJump = false;
	BetterGun = false;
	Exp = 0;
	mustRead = true;
}
