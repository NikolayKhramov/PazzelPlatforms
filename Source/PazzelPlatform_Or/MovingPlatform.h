// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PAZZELPLATFORM_OR_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
private:
	UPROPERTY()
		FVector StartLocation;
	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;
	
	
public:
	AMovingPlatform();

	UPROPERTY(EditAnywhere)
		float PlatformVelocity = 15.f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
		FVector TargetLocation;
	UPROPERTY()
		FVector GlobalTargetLocation;
	UFUNCTION()
		void AddActiveTrigger();

	UFUNCTION()
		void RemoveActiveTrigger();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
