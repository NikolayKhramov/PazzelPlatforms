// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuWidget.h"
#include "FinishMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PAZZELPLATFORM_OR_API UFinishMenuWidget : public UMenuWidget
{
	GENERATED_BODY()
	

public:

	UFUNCTION()
		void ToMain();

protected:

	virtual bool Initialize() override;

private:

	UFUNCTION()
		void QuitGame();
	UPROPERTY(meta = (BindWidget))
		class UButton* GoToMainButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton2;
};
