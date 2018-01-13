// Fill out your copyright notice in the Description page of Project Settings.

#include "VideoMenuCPP.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/Engine.h"

void UVideoMenuCPP::FillScreenResolutionsComboBox()
{
	if (ScreenResolutionsComboBoxCPP)
	{
		TArray<FString> resolutions = GetSupportedScreenResolutions();
		for (size_t i = 0; i < resolutions.Num(); ++i)
		{
			ScreenResolutionsComboBoxCPP->AddOption(resolutions[i]);
		}
	}
	ScreenResolutionsComboBoxCPP->SetSelectedOption(FString::FromInt(GSystemResolution.ResX) + TEXT(" x ") + FString::FromInt(GSystemResolution.ResY));
}

TArray<FString>  UVideoMenuCPP::GetSupportedScreenResolutions()
{
	TArray<FString> screenResolutions;
	TArray <FScreenResolutionRHI>RHIScreenResolutions;
	if (RHIGetAvailableResolutions(RHIScreenResolutions, true))
		for (size_t i = 0; i < RHIScreenResolutions.Num(); i++) {
			if (RHIScreenResolutions[i].Width >= 600 && RHIScreenResolutions[i].Height >= 600)
				screenResolutions.Add(
					FString::FromInt(RHIScreenResolutions[i].Width) +
					TEXT(" x ") +
					FString::FromInt(RHIScreenResolutions[i].Height)
				);
		}
	return screenResolutions;
}

void UVideoMenuCPP::ApplyResolution()
{
	EWindowMode::Type windowMode = EWindowMode::Windowed;
	UGameUserSettings* settings = UGameUserSettings::GetGameUserSettings();
	if (settings)
		windowMode = settings->GetFullscreenMode();
	FString resolution = ScreenResolutionsComboBoxCPP->GetSelectedOption();
	TArray<FString>resolutionSize;
	TArray<FString> &resolutionSizeRef = resolutionSize;
	resolution.ParseIntoArray(resolutionSizeRef, TEXT(" "), 1);
	int32 width = FCString::Atoi(*(resolutionSize[0]));
	int32 height = FCString::Atoi(*(resolutionSize[2]));
	settings->RequestResolutionChange(width, height, windowMode, false);
	settings->SetScreenResolution(FIntPoint(width, height));
}

void UVideoMenuCPP::InitializeFullScreenCheckBoxValue()
{
	if (FullScreenCheckBoxCPP)
	{
		UGameUserSettings* gameUserSettings = UGameUserSettings::GetGameUserSettings();
		EWindowMode::Type windowMode = gameUserSettings->GetFullscreenMode();
		if (windowMode == EWindowMode::Fullscreen)
		{
			FullScreenCheckBoxCPP->SetCheckedState(ECheckBoxState::Checked);
		}
		else
		{
			FullScreenCheckBoxCPP->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
}

void UVideoMenuCPP::ApplyFullScreen()
{
	UGameUserSettings* settings = GEngine->GetGameUserSettings();
	if (!settings)
	{
		return;
	}
	if (FullScreenCheckBoxCPP)
	{
		if (FullScreenCheckBoxCPP->CheckedState == ECheckBoxState::Checked)
		{

			settings->SetFullscreenMode(EWindowMode::Fullscreen);
			settings->RequestResolutionChange(GSystemResolution.ResX, GSystemResolution.ResY, EWindowMode::Fullscreen, false);
		}
		else
		{
			settings->RequestResolutionChange(GSystemResolution.ResX, GSystemResolution.ResY, EWindowMode::Windowed, false);
			settings->SetFullscreenMode(EWindowMode::Windowed);
		}
	}
}

void UVideoMenuCPP::InitializeAntiAliasingHorizontalBoxContent()
{
	UGameUserSettings* settings = UGameUserSettings::GetGameUserSettings();
	if (!settings)
	{
		return;
	}
	int32 antiAliasing = settings->ScalabilityQuality.AntiAliasingQuality;
	if (AntiAliasingComboBoxCPP)
	{
		AntiAliasingComboBoxCPP->AddOption(TEXT("Low"));
		AntiAliasingComboBoxCPP->AddOption(TEXT("Medium"));
		AntiAliasingComboBoxCPP->AddOption(TEXT("High"));
		AntiAliasingComboBoxCPP->AddOption(TEXT("Epic"));

		if (antiAliasing == 0)
			AntiAliasingComboBoxCPP->SetSelectedOption(TEXT("Low"));
		else if (antiAliasing == 2)
			AntiAliasingComboBoxCPP->SetSelectedOption(TEXT("Medium"));
		else if (antiAliasing == 4)
			AntiAliasingComboBoxCPP->SetSelectedOption(TEXT("High"));
		else if (antiAliasing == 6)
			AntiAliasingComboBoxCPP->SetSelectedOption(TEXT("Epic"));
	}
}

void UVideoMenuCPP::ApplyAntiAliasing()
{
	UGameUserSettings* settings = UGameUserSettings::GetGameUserSettings();
	if (!settings)
	{
		return;
	}
	if (AntiAliasingComboBoxCPP->GetSelectedOption() == TEXT("Low"))
	{
		settings->ScalabilityQuality.AntiAliasingQuality = 0;
	}
	else if (AntiAliasingComboBoxCPP->GetSelectedOption() == TEXT("Medium"))
	{
		settings->ScalabilityQuality.AntiAliasingQuality = 2;
	}
	else if (AntiAliasingComboBoxCPP->GetSelectedOption() == TEXT("High"))
	{
		settings->ScalabilityQuality.AntiAliasingQuality = 4;
	}
	else if (AntiAliasingComboBoxCPP->GetSelectedOption() == TEXT("Epic"))
	{
		settings->ScalabilityQuality.AntiAliasingQuality = 6;
	}
	settings->ConfirmVideoMode();
	settings->ApplyNonResolutionSettings();
	settings->SaveSettings();
}

void UVideoMenuCPP::ApplyShadows()
{
	UGameUserSettings* settings = UGameUserSettings::GetGameUserSettings();
	if (!settings)
	{
		return;
	}
	if (ShadowsComboBoxCPP->GetSelectedOption() == TEXT("Low"))
	{
		settings->SetShadowQuality(0);
	}
	else if (ShadowsComboBoxCPP->GetSelectedOption() == TEXT("Medium"))
	{
		settings->SetShadowQuality(1);
	}
	else if (ShadowsComboBoxCPP->GetSelectedOption() == TEXT("High"))
	{
		settings->SetShadowQuality(2);
	}
	else if (ShadowsComboBoxCPP->GetSelectedOption() == TEXT("Epic"))
	{
		settings->SetShadowQuality(3);
	}
	settings->ConfirmVideoMode();
	settings->ApplyNonResolutionSettings();
	settings->SaveSettings();

}

void UVideoMenuCPP::InitializeShadowsHorizontalBoxContent()
{
	UGameUserSettings* settings = UGameUserSettings::GetGameUserSettings();
	if (!settings)
	{
		return;
	}
	int32 shadowQuality = settings->GetShadowQuality();
	if (ShadowsComboBoxCPP)
	{
		ShadowsComboBoxCPP->AddOption(TEXT("Low"));
		ShadowsComboBoxCPP->AddOption(TEXT("Medium"));
		ShadowsComboBoxCPP->AddOption(TEXT("High"));
		ShadowsComboBoxCPP->AddOption(TEXT("Epic"));
		ShadowsComboBoxCPP->SetSelectedOption(TEXT("Low"));
		if (shadowQuality == 0)
			ShadowsComboBoxCPP->SetSelectedOption(TEXT("Low"));
		else if (shadowQuality == 1)
			ShadowsComboBoxCPP->SetSelectedOption(TEXT("Medium"));
		else if (shadowQuality == 2)
			ShadowsComboBoxCPP->SetSelectedOption(TEXT("High"));
		else if (shadowQuality == 3)
			ShadowsComboBoxCPP->SetSelectedOption(TEXT("Epic"));
	}
}
