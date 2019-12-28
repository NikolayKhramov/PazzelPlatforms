// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRowWidget.h"
#include "Components/Button.h"
#include "MenuSystem/MainMenuCPP.h"

void UServerRowWidget::SetUp(UMainMenuCPP* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	IndexServerButton->OnClicked.AddDynamic(this, &UServerRowWidget::OnIndexServerPressed);

}

void UServerRowWidget::OnIndexServerPressed()
{ 
	Parent->SelectIndex(Index);
}
