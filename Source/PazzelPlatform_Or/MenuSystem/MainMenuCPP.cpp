// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuCPP.h"
#include "Engine/Engine.h"

#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "GameFramework/PlayerController.h"



bool UMainMenuCPP::Initialize() {
	bool is_succeed = Super::Initialize();
	if (!is_succeed)
		return false;

	Host->OnClicked.AddDynamic(this, &UMainMenuCPP::HostServer);
	Join->OnClicked.AddDynamic(this, &UMainMenuCPP::SetUpJoinMenu);
	CancelButton->OnClicked.AddDynamic(this, &UMainMenuCPP::BackToMainMenu);
	ConnectButton->OnClicked.AddDynamic(this, &UMainMenuCPP::JoinServer);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuCPP::QuitGame);



	return true;
}




void UMainMenuCPP::HostServer()
{
	
	if (MenuInterface != nullptr) {

		MenuInterface->Host();
	}
	
}

void UMainMenuCPP::JoinServer()
{
	FString IPAdress;
	if (!ensure(TextBox != nullptr))
		return;
	IPAdress = TextBox->GetText().ToString();
	
	MenuInterface->Join(IPAdress);
}

void UMainMenuCPP::SetUpJoinMenu()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);

}

void UMainMenuCPP::BackToMainMenu()
{
	FText NoText;
	TextBox->SetText(NoText);
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenuCPP::QuitGame()
{

	UWorld* World = GetWorld();
	if (!ensure(World!= nullptr))
		return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr))
		return;

	PlayerController->ConsoleCommand("Quit");

}
