// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	virtual void LoadMainMenu()override;

	UFUNCTION(BlueprintCallable)
		void LoadMenu();
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
};
