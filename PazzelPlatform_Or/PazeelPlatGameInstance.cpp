// Fill out your copyright notice in the Description page of Project Settings.

#include "PazeelPlatGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenuCPP.h"
#include "MenuSystem/MenuWidget.h"
#include "InGameMenu.h"

const static FName SESSION_NAME = TEXT("My Session Game");

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

void UPazeelPlatGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Start finding session "));
		SessionSearch->bIsLanQuery = true;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}

}

void UPazeelPlatGameInstance::LoadMenuWidget()
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


void UPazeelPlatGameInstance::Host() {

	if (SessionInterface.IsValid()) {
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr) {
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else {
			CreateSession();
		}
	}

}
void UPazeelPlatGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	
	if (!Success) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not create session"));
		return;
	}

	if (Menu != nullptr) {

		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))
		return;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
		return;

	World->ServerTravel("/Game/ThirdPersonBP/Maps/PazzleMap?listen");

	

}

void UPazeelPlatGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success) {
		CreateSession();
	}

}

void UPazeelPlatGameInstance::OnFindSessionsComplete(bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("Finished finding session "));
	if (Success && SessionSearch.IsValid()) {
		//RefreshServerList();

		TArray<FString> ServerNames;
		for (auto& Result : SessionSearch->SearchResults) {
			UE_LOG(LogTemp, Warning, TEXT("Found session:  %s"), *Result.GetSessionIdStr());
			ServerNames.Add(Result.GetSessionIdStr());
		}
		Menu->SetServerListNames(ServerNames);
	}
}

void UPazeelPlatGameInstance::CreateSession()
{
	if (SessionInterface.IsValid()) {
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.NumPublicConnections = 2;

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPazeelPlatGameInstance::Join(const FString& Adress)
{
	/*UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))
		return;


	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))
		return;

	PlayerController->ClientTravel(Adress, ETravelType::TRAVEL_Absolute);*/

	if (Menu != nullptr) {
		//Menu->SetServerListNames({ "Test1" ,  "Test2" });
		//Menu->Teardown();
	}
}

void UPazeelPlatGameInstance::Init()
{
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (SubSystem != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Found subsystem %s"), *SubSystem->GetSubsystemName().ToString());
		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPazeelPlatGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPazeelPlatGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPazeelPlatGameInstance::OnFindSessionsComplete);

			
		} 
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));

	}

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
