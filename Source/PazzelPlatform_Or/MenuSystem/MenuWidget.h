// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"

#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PAZZELPLATFORM_OR_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void SetUp();
	UFUNCTION()
		void Teardown();
	UFUNCTION()
		void FromInGameMenuToMain();

	void SetMenuInterface(IMenuInterface* MenuInterface);

protected:
	IMenuInterface* MenuInterface;

	virtual bool Initialize() override;


};
