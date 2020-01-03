// Fill out your copyright notice in the Description page of Project Settings.

#include "FinishMenuWidget.h"
#include "Components/Button.h"



bool UFinishMenuWidget::Initialize() {
	bool is_succeed = Super::Initialize();
	

	ExitButton->OnClicked.AddDynamic(this, &UFinishMenuWidget::QuitGame);
	ExitButton2->OnClicked.AddDynamic(this, &UFinishMenuWidget::QuitGame);
	GoToMainButton->OnClicked.AddDynamic(this, &UFinishMenuWidget::ToMain);

	return true;
}


void UFinishMenuWidget::ToMain() {

	if (MenuInterface != nullptr) {
		Teardown();
		MenuInterface->LoadMainMenu();
	}

}

void UFinishMenuWidget::QuitGame()
{

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
		return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr))
		return;

	PlayerController->ConsoleCommand("Quit");

}

