// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrGameInstance.h"

UMnShtrGameInstance::UMnShtrGameInstance(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	mustRead = false;
	location = FVector();
	rotation = FRotator();
	playerName = TEXT("");
}

