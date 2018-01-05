// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "VideoMenuCPP.generated.h"
/**
 * 
 */
UCLASS()
class MINISHOOTER_API UVideoMenuCPP : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category="MnShtr")
		UComboBoxString *ScreenResolutionsComboBoxCPP;
	UFUNCTION(BlueprintCallable, Category="MnShtr")
		void FillScreenResolutionsComboBox();
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ApplyResolution();

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UCheckBox *FullScreenCheckBoxCPP;
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ApplyFullScreen();
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void InitializeFullScreenCheckBoxValue();

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UComboBoxString *AntiAliasingComboBoxCPP;
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ApplyAntiAliasing();
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void InitializeAntiAliasingHorizontalBoxContent();

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UComboBoxString *ShadowsComboBoxCPP;
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void ApplyShadows();
	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void InitializeShadowsHorizontalBoxContent();
private:
	TArray<FString> GetSupportedScreenResolutions();

};
