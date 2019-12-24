// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
		ActiveTriggers--;
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (ActiveTriggers > 0) {//when triggered than implement this logic (1 - by default)

		if (HasAuthority()) {//change location on the server

			FVector Location = GetActorLocation();
			FVector Direction;
			float JourneyLength = (GlobalTargetLocation - StartLocation).Size();
			float JourneyTravelled = (Location - StartLocation).Size();

			//handling moving from one point to another via 
			//seting new TargetLocation after reached one
			if (JourneyTravelled > JourneyLength) {
				FVector tmp = StartLocation;
				StartLocation = GlobalTargetLocation;
				GlobalTargetLocation = tmp;
			}

			Direction = (GlobalTargetLocation - StartLocation).GetSafeNormal();

			Location += PlatformVelocity * DeltaTime * Direction;

			SetActorLocation(Location);

		}

	}

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	StartLocation = GetActorLocation();

	if (HasAuthority()) {//set replications on the server
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}