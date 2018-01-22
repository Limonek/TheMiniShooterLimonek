// Fill out your copyright notice in the Description page of Project Settings.

#include "ProfileWidgetCPP.h"
#include "MnShtrGameInstance.h"

void UProfileWidgetCPP::InitializeContent()
{
	UWorld* world = GetWorld();
	UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
	if (!gameInstance)
	{
		return;
	}
	if (gameInstance->CanRun)
	{
		RunTextBoxCPP->SetVisibility(ESlateVisibility::Visible);
		RunButtonCPP->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		RunTextBoxCPP->SetVisibility(ESlateVisibility::Collapsed);
		RunButtonCPP->SetVisibility(ESlateVisibility::Visible);
	}

	if (gameInstance->CanJump)
	{
		JumpTextBoxCPP->SetVisibility(ESlateVisibility::Visible);
		JumpButtonCPP->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		JumpTextBoxCPP->SetVisibility(ESlateVisibility::Collapsed);
		JumpButtonCPP->SetVisibility(ESlateVisibility::Visible);
	}

	if (gameInstance->BetterGun)
	{
		GunTextBoxCPP->SetVisibility(ESlateVisibility::Visible);
		GunButtonCPP->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		GunTextBoxCPP->SetVisibility(ESlateVisibility::Collapsed);
		GunButtonCPP->SetVisibility(ESlateVisibility::Visible);
	}
	NameTextBoxCPP->SetText(gameInstance->PlayerName);
	ExpTextBoxCPP->SetText(FText::AsNumber(gameInstance->Exp));
}

void UProfileWidgetCPP::BuyRunButtonClickCPP()
{
	UWorld* world = GetWorld();
	UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
	if (gameInstance->Exp > 100)
	{
		gameInstance->CanRun = true;
		RunButtonCPP->SetVisibility(ESlateVisibility::Collapsed);
		RunTextBoxCPP->SetVisibility(ESlateVisibility::Visible);
		gameInstance->Exp = gameInstance->Exp - 100;
	}
}

void UProfileWidgetCPP::BuyJumpButtonClickCPP()
{
	UWorld* world = GetWorld();
	UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
	if (gameInstance->Exp > 100)
	{
		gameInstance->CanJump = true;
		JumpButtonCPP->SetVisibility(ESlateVisibility::Collapsed);
		JumpTextBoxCPP->SetVisibility(ESlateVisibility::Visible);
		gameInstance->Exp = gameInstance->Exp - 100;
	}
}

void UProfileWidgetCPP::BuyGunButtonClickCPP()
{
	UWorld* world = GetWorld();
	UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
	if (gameInstance->Exp > 100)
	{
		gameInstance->BetterGun = true;
		GunButtonCPP->SetVisibility(ESlateVisibility::Collapsed);
		GunTextBoxCPP->SetVisibility(ESlateVisibility::Visible);
		gameInstance->Exp = gameInstance->Exp - 100;
	}
}

