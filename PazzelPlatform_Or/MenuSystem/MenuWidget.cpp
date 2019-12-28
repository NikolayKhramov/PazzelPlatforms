// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"

void UMenuWidget::SetUp()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
		return;


	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr))
		return;

	this->bIsFocusable = true;

	FInputModeUIOnly InputData;
	InputData.SetWidgetToFocus(this->TakeWidget());
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputData);
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::Teardown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
		return;


	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr))
		return;

	this->bIsFocusable = false;

	FInputModeGameOnly InputData;


	PlayerController->SetInputMode(InputData);
	PlayerController->bShowMouseCursor = false;
}

void UMenuWidget::FromInGameMenuToMain()
{
	Teardown();
	

}


void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface) {

	this->MenuInterface = MenuInterface;

}

bool UMenuWidget::Initialize()
{
	bool is_succeed = Super::Initialize();
	if (!is_succeed)
		return false;


	return true;
}
