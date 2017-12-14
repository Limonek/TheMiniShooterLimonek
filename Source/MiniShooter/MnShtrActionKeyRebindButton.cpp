// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrActionKeyRebindButton.h"

void UMnShtrActionKeyRebindButton::OnClick()
{
	if (optionsWidget)
	{
		optionsWidget->ActionButton = this;
	}
}



