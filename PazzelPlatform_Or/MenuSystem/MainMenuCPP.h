// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "MainMenuCPP.generated.h"

/**
 * 
 */
UCLASS()
class PAZZELPLATFORM_OR_API UMainMenuCPP : public UMenuWidget
{
	GENERATED_BODY()

public:

	UMainMenuCPP(const FObjectInitializer& ObjectInitializer);

	void SetServerListNames(TArray<FString> ServerNames);

	void SelectIndex(uint32 index);

protected:

		virtual bool Initialize() override;
private:

	UFUNCTION()
		void HostServer();
	UFUNCTION()
		void JoinServer();
	UFUNCTION()
		void SetUpJoinMenu();
	UFUNCTION()
		void BackToMainMenu();
	UFUNCTION()
		void QuitGame();
	

	UPROPERTY( meta = (BindWidget))
		class UButton* Host;
	UPROPERTY(meta = (BindWidget))
		class UButton* Join;
	UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* ConnectButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;
	

	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* ServerList;
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;
	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

	TSubclassOf<UUserWidget> ServerRowClass;
	class UServerRowWidget* ServerRow;

	TOptional<uint32> SelectedIndex;

};
