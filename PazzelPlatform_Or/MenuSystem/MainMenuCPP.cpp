// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuCPP.h"
#include "Engine/Engine.h"

#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "Components/PanelWidget.h"
#include "ServerRowWidget.h"
#include "UObject/ConstructorHelpers.h"



void UMainMenuCPP::SetServerListNames(TArray<FString> ServerNames)
{

	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr))
		return;

	ServerList->ClearChildren();

	uint32 i = 0;
	for (const FString& ServerName : ServerNames)
	{
		ServerRow = CreateWidget<UServerRowWidget>(World, ServerRowClass);
		ServerRow->ServerName->SetText(FText::FromString(ServerName));
		ServerRow->SetUp(this, i);
		++i;
		if (!ensure(ServerList != nullptr))
			return;
		ServerList->AddChild(ServerRow);
	}

}

void UMainMenuCPP::SelectIndex(uint32 index)
{
	SelectedIndex = index;
}

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

UMainMenuCPP::UMainMenuCPP(const FObjectInitializer& ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> RowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(RowBPClass.Class != nullptr))
		return;
	ServerRowClass = RowBPClass.Class;

}


void UMainMenuCPP::HostServer()
{
	
	if (MenuInterface != nullptr) {

		MenuInterface->Host();
	}
	
}

void UMainMenuCPP::JoinServer()
{
	/*FString IPAdress;
	if (!ensure(TextBox != nullptr))
		return;
	IPAdress = TextBox->GetText().ToString();*/
	
	if (SelectedIndex.IsSet()) {
		UE_LOG(LogTemp, Warning, TEXT("Selected index %d."), SelectedIndex.GetValue());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Selected no index "));
	}

	MenuInterface->Join("");

}

void UMainMenuCPP::SetUpJoinMenu()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
	if (MenuInterface != nullptr) {
		MenuInterface->RefreshServerList();
	}
}

void UMainMenuCPP::BackToMainMenu()
{
	//FText NoText;
	//TextBox->SetText(NoText);
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

