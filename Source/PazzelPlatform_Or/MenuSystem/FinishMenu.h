// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FinishMenu.generated.h"

/**
 * 
 */
UCLASS()
class PAZZELPLATFORM_OR_API UFinishMenu : public UUserWidget
{
	GENERATED_BODY()
	

private:

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;
};
