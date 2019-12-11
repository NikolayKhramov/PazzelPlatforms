// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PAZZELPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMovingPlatform();

	UPROPERTY(EditAnywhere)
		float PlatformVelocity = 15.f;

	UPROPERTY(EditAnywhere,Meta=(MakeEditWidget=true))
		FVector TargetLocation;

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
