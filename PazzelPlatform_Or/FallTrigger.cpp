// Fill out your copyright notice in the Description page of Project Settings.

#include "FallTrigger.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AFallTrigger::AFallTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Volume"));
	if (!ensure(TriggerVolume != nullptr))
		return;

	RootComponent = TriggerVolume;

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AFallTrigger::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AFallTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFallTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	OtherActor->SetActorLocation(SpawnLocation);

	/*for (AActor* Character : Characters) {
		if (Character->GetActorLocation() == OtherActor->GetActorLocation()) {
			OtherActor->SetActorLocation(SpawnLocation);
		}
	}*/
}

// Called every frame
void AFallTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

