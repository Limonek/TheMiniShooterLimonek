// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrAxisKeyRebindButton.h"

void UMnShtrAxisKeyRebindButton::OnClick()
{
	if (optionsWidget)
	{
		optionsWidget->AxisButton = this;
	}
}


