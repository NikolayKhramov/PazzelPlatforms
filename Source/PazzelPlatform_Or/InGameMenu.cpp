// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "Components/Button.h"

void UInGameMenu::OnCancelButtonInGameMenuCliked() {
	UMenuWidget::Teardown();
	//CancelButtonInGameMenu->OnClicked;
}

void UInGameMenu::QuitPressed()
{
	if (MenuInterface!= nullptr) {
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}

bool UInGameMenu::Initialize() {
	bool is_succeed = Super::Initialize();
	if (!is_succeed)
		return false;

	CancelButtonInGameMenu->OnClicked.AddDynamic(this, &UMenuWidget::Teardown);
	QuitButtonInGameMenu->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);


	return true;
}