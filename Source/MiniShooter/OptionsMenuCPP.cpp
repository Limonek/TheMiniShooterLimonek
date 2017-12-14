// Fill out your copyright notice in the Description page of Project Settings.

#include "OptionsMenuCPP.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "UObject/Class.h"
#include "MnShtrAxisKeyRebindButton.h"
#include "MnShtrActionKeyRebindButton.h"
#include "GameFramework/InputSettings.h"
#include "UObject/UObjectIterator.h"
#include "GameFramework/PlayerInput.h"

void UOptionsMenuCPP::ChangeActionBinding(FKey key)
{
	UTextBlock *textBlock;
	textBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	textBlock->SetText(key.GetDisplayName());
	ActionButton->ClearChildren();
	ActionButton->AddChild(textBlock);
	UInputSettings* inputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	if (!inputSettings)
		return;
	TArray<FInputActionKeyMapping>& Actions = inputSettings->ActionMappings;
	for (FInputActionKeyMapping& mapping : Actions)
		if (mapping.ActionName == ActionButton->ActionMapping.ActionName && mapping.Key == ActionButton->ActionMapping.Key)
		{
			mapping.Key = key;
			const_cast<UInputSettings*>(inputSettings)->SaveKeyMappings();
			ActionButton->ActionMapping = mapping;
			break;
		}
	for (TObjectIterator<UPlayerInput> It; It; ++It)
		It->ForceRebuildingKeyMaps(true);
	ActionButton->SetIsEnabled(true);
	ActionButton = nullptr;
}

void UOptionsMenuCPP::ChangeAxisBinding(FKey key)
{
	UTextBlock *textBlock;
	textBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	textBlock->SetText(key.GetDisplayName());
	AxisButton->ClearChildren();
	AxisButton->AddChild(textBlock);
	UInputSettings* inputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	if (!inputSettings)
		return;
	TArray<FInputAxisKeyMapping>& Axis = inputSettings->AxisMappings;
	for (FInputAxisKeyMapping& mapping : Axis)
		if (mapping.AxisName == AxisButton->AxisMapping.AxisName && mapping.Key == AxisButton->AxisMapping.Key)
		{
			mapping.Key = key;
			const_cast<UInputSettings*>(inputSettings)->SaveKeyMappings();
			AxisButton->AxisMapping = mapping;
			break;
		}
	for (TObjectIterator<UPlayerInput> It; It; ++It)
		It->ForceRebuildingKeyMaps(true);
	AxisButton->SetIsEnabled(true);
	AxisButton = nullptr;
}

FReply UOptionsMenuCPP::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	if (ActionButton)
		ChangeActionBinding(InMouseEvent.GetEffectingButton());
	if (AxisButton)
		ChangeAxisBinding(InMouseEvent.GetEffectingButton());
	return FReply::Handled();
}

FReply UOptionsMenuCPP::NativeOnKeyDown(const FGeometry & InGeometry, const FKeyEvent & InKeyEvent)
{
	if (ActionButton)
		ChangeActionBinding(InKeyEvent.GetKey());
	if (AxisButton)
		ChangeAxisBinding(InKeyEvent.GetKey());
	return FReply::Handled();
}

void UOptionsMenuCPP::SetTextAndActionMapping(UMnShtrActionKeyRebindButton* button, FInputActionKeyMapping mapping)
{
	UTextBlock *textBlock;
	button->optionsWidget = this;
	button->ActionMapping = mapping;
	textBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	textBlock->SetText(FText::FromName(mapping.Key.GetFName()));
	button->AddChild(textBlock);
}

void UOptionsMenuCPP::SetTextAndAxisMapping(UMnShtrAxisKeyRebindButton* button, FInputAxisKeyMapping mapping)
{
	UTextBlock *textBlock;
	button->optionsWidget = this;
	button->AxisMapping = mapping;
	textBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	textBlock->SetText(FText::FromName(mapping.Key.GetFName()));
	button->AddChild(textBlock);
}

void UOptionsMenuCPP::ReverseMouse(bool reverse)
{
	float scale;
	if (reverse)
		scale = 1;
	else
		scale = -1;
	UInputSettings* inputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	if (!inputSettings)
		return;
	TArray<FInputAxisKeyMapping>& Axis = inputSettings->AxisMappings;
	for (FInputAxisKeyMapping& mapping : Axis)
		if (mapping.AxisName == "LookUp")
		{
			mapping.Scale = scale;
			const_cast<UInputSettings*>(inputSettings)->SaveKeyMappings();
			break;
		}
	for (TObjectIterator<UPlayerInput> It; It; ++It)
		It->ForceRebuildingKeyMaps(true);
}

void UOptionsMenuCPP::AddBindingsButtons()
{
	const UInputSettings* Settings = GetDefault<UInputSettings>();
	if (!Settings) return;

	const TArray<FInputActionKeyMapping>& Actions = Settings->ActionMappings;

	for (const FInputActionKeyMapping& mapping : Actions)
	{
		if (mapping.ActionName == "Fire")
			SetTextAndActionMapping(FireActionButtonCPP, mapping);
		if (mapping.ActionName == "Jump")
			SetTextAndActionMapping(JumpActionButtonCPP, mapping);
		if (mapping.ActionName == "PauseMenu")
			SetTextAndActionMapping(PauseMenuActionButtonCPP, mapping);
		if (mapping.ActionName == "Run")
			SetTextAndActionMapping(RunActionButtonCPP, mapping);
	}

	const TArray<FInputAxisKeyMapping>& Axis = Settings->AxisMappings;

	for (const FInputAxisKeyMapping& mapping : Axis)
	{
		if (mapping.AxisName == "MoveForward"&&mapping.Scale == 1)
			SetTextAndAxisMapping(MoveForwardAxisButtonCPP, mapping);
		if (mapping.AxisName == "MoveForward"&&mapping.Scale == -1)
			SetTextAndAxisMapping(MoveBackwardAxisButtonCPP, mapping);
		if (mapping.AxisName == "MoveRight"&&mapping.Scale == 1)
			SetTextAndAxisMapping(MoveRightAxisButtonCPP, mapping);
		if (mapping.AxisName == "MoveRight"&&mapping.Scale == -1)
			SetTextAndAxisMapping(MoveLeftAxisButtonCPP, mapping);
		if (mapping.AxisName == "LookUp"&&mapping.Scale == -1)
			ReverseMouseCheckBoxCPP->SetCheckedState(ECheckBoxState::Unchecked);
		else if (mapping.AxisName == "LookUp"&&mapping.Scale == 1)
			ReverseMouseCheckBoxCPP->SetCheckedState(ECheckBoxState::Checked);
	}
}
