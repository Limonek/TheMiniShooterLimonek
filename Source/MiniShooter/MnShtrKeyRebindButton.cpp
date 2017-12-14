// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrKeyRebindButton.h"
#include "OptionsMenuCPP.h"
#include "Components/TextBlock.h"

UMnShtrKeyRebindButton::UMnShtrKeyRebindButton()
{
	OnClicked.AddDynamic(this, &UMnShtrKeyRebindButton::OnClick);
	OnClicked.AddDynamic(this, &UMnShtrKeyRebindButton::DisableButton);
	OnClicked.AddDynamic(this, &UMnShtrKeyRebindButton::SetWaitingText);
}

void UMnShtrKeyRebindButton::DisableButton()
{
	SetIsEnabled(false);
}

void UMnShtrKeyRebindButton::SetWaitingText()
{
	ClearChildren();
	UTextBlock *textBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());;
	textBlock->SetText(FText::FromString(TEXT("Define new key")));
	AddChild(textBlock);
}



