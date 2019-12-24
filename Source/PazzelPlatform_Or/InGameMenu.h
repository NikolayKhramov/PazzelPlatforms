// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PAZZELPLATFORM_OR_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void OnCancelButtonInGameMenuCliked();
	UFUNCTION()
		void QuitPressed();
protected:

	virtual bool Initialize() override;

private:
	UPROPERTY( meta = (BindWidget))
		class UButton* CancelButtonInGameMenu;
	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButtonInGameMenu;

};
