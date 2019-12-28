// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class PAZZELPLATFORM_OR_API UServerRowWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ServerName;

	void SetUp(class UMainMenuCPP* InParent, uint32 InIndex);

	UFUNCTION()
		void OnIndexServerPressed();
	UPROPERTY()
	class UMainMenuCPP* Parent;
	uint32 Index;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* IndexServerButton;
};
