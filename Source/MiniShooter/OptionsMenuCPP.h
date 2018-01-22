// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/CheckBox.h"
#include "GameFramework/InputSettings.h"
#include "OptionsMenuCPP.generated.h"

using namespace UP;

class UMnShtrAxisKeyRebindButton;
class UMnShtrActionKeyRebindButton;

/**
 *
 */
UCLASS()
class MINISHOOTER_API UOptionsMenuCPP : public UUserWidget
{
	GENERATED_BODY()

	virtual FReply NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)override;
	virtual FReply NativeOnKeyDown(const FGeometry & InGeometry, const FKeyEvent & InKeyEvent)override;

public:
	UFUNCTION(BlueprintCallable, Category="MnShtr")
	void ReverseMouse(bool reverse);

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UScrollBox* ButtonsBoxCPP;

	UFUNCTION(BlueprintCallable, Category = "MnShtr")
		void AddBindingsButtons();

	//Action Bindings Button
	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UMnShtrActionKeyRebindButton* FireActionButtonCPP;
	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UMnShtrActionKeyRebindButton* JumpActionButtonCPP;
	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UMnShtrActionKeyRebindButton* PauseMenuActionButtonCPP;
	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UMnShtrActionKeyRebindButton* RunActionButtonCPP;

	//Axis Bindings Button
	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UMnShtrAxisKeyRebindButton* MoveForwardAxisButtonCPP;
	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UMnShtrAxisKeyRebindButton* MoveBackwardAxisButtonCPP;
	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UMnShtrAxisKeyRebindButton* MoveRightAxisButtonCPP;
	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UMnShtrAxisKeyRebindButton* MoveLeftAxisButtonCPP;

	UPROPERTY(BlueprintReadWrite, Category = "MnShtr")
		UCheckBox* ReverseMouseCheckBoxCPP;
	
	UPROPERTY()
		UMnShtrActionKeyRebindButton* ActionButton;
	UPROPERTY()
		UMnShtrAxisKeyRebindButton* AxisButton;
private:
	void SetTextAndActionMapping(UMnShtrActionKeyRebindButton* button, FInputActionKeyMapping mapping);
	void SetTextAndAxisMapping(UMnShtrAxisKeyRebindButton* button, FInputAxisKeyMapping mapping);
	void ChangeActionBinding(FKey key);
	void ChangeAxisBinding(FKey key);
};
