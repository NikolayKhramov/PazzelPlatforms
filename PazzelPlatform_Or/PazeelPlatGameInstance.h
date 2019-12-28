// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h" 
#include "MenuSystem/MenuInterface.h"
#include "PazeelPlatGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PAZZELPLATFORM_OR_API UPazeelPlatGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UPazeelPlatGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void LoadMainMenu() override;
	void RefreshServerList() override;

	UFUNCTION(BlueprintCallable)
		void LoadMenuWidget();
	UFUNCTION(BlueprintCallable)
		void InGameLoadMenu();
	UFUNCTION(BlueprintCallable)
		void InGameTeardownMenu();

	UFUNCTION(Exec)
		void Host() override;
	UFUNCTION(Exec)
		void Join(const FString& Adress)override;

protected:
	
	virtual void Init() override;
private:
	TSubclassOf<UUserWidget> MenuClass;
	TSubclassOf<UUserWidget> InGameMenuClass;
	class UInGameMenu* InGameMenu;
	class UMainMenuCPP* Menu;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);

	void CreateSession();
};
