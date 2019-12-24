// Fill out your copyright notice in the Description page of Project Settings.

#include "PazeelPlatGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenuCPP.h"
#include "MenuSystem/MenuWidget.h"
#include "InGameMenu.h"



void UPazeelPlatGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))
		return;

	/*
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
		return;
	World->ServerTravel("/Game/MenuSystem/Maps/StartMenuLevel?listen");
	*/

	PlayerController->ClientTravel("/Game/MenuSystem/Maps/StartMenuLevel", ETravelType::TRAVEL_Absolute);

}

void UPazeelPlatGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr))
		return;

	Menu = CreateWidget<UMainMenuCPP>(this, MenuClass);
	if (!ensure(Menu != nullptr))
		return;

	Menu->SetUp();

	Menu->SetMenuInterface(this);

}

void UPazeelPlatGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr))
		return;
	
	InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
	if (!ensure(InGameMenu != nullptr))
		return;

	InGameMenu->SetUp();

	InGameMenu->SetMenuInterface(this);
}

void UPazeelPlatGameInstance::InGameTeardownMenu()
{
	//InGameMenu->SetMenuInterface(this);

	InGameMenu->OnCancelButtonInGameMenuCliked();

	//InGameMenu->Teardown();
	//InGameMenu->SetMenuInterface(this);
}


void UPazeelPlatGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))
		return;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
		return;

	World->ServerTravel("/Game/ThirdPersonBP/Maps/PazzleMap?listen");

	Menu->Teardown();

}

void UPazeelPlatGameInstance::Join(const FString& Adress)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))
		return;


	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))
		return;

	PlayerController->ClientTravel(Adress, ETravelType::TRAVEL_Absolute);

	Menu->Teardown();
}

void UPazeelPlatGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass -> GetName());

}


UPazeelPlatGameInstance::UPazeelPlatGameInstance(const FObjectInitializer& ObjectInitializer) {

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr))
		return;

	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr))
		return;

	InGameMenuClass = InGameMenuBPClass.Class;
	
	
}
