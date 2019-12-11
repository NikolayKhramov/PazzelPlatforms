// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) {//change location on the server

		FVector Location = GetActorLocation();
		//FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
		//Vector Direction = (TargetLocation - Location).GetSafeNormal();

		Location += FVector(PlatformVelocity * DeltaTime,0,0);
		SetActorLocation(Location);
	}

	
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()){//set replications on the server
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}
