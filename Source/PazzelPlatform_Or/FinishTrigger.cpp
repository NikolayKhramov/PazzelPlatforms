// Fill out your copyright notice in the Description page of Project Settings.

#include "FinishTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AFinishTrigger::AFinishTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Volume"));
	if (!ensure(TriggerVolume != nullptr))
		return;

	RootComponent = TriggerVolume;


	ConstructorHelpers::FClassFinder<AActor> CharacterBPClass(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter"));
	if (!ensure(CharacterBPClass.Class != nullptr))
		return;

	CharacterClass = CharacterBPClass.Class;


	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AFinishTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AFinishTrigger::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AFinishTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(this, CharacterClass, Characters);

	
	for (AActor* Character : Characters) {

		if (!ensure(Character != nullptr))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Found Character: %s"), *Character->GetName());
	}

}

void AFinishTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	UGameplayStatics::GetAllActorsOfClass(this, CharacterClass, Characters);


	for (AActor* Character : Characters) {

		if (!ensure(Character != nullptr))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Found Character: %s"), *Character->GetName());
	}

}

void AFinishTrigger::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{




}

// Called every frame
void AFinishTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

