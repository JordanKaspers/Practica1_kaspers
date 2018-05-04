// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"


// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();
  if (!VolumeToOpenDoor)
  {
    UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate!"), *GetOwner()->GetName());
  }
}

// Called every frame
void UDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // Poll the Trigger Volume
  if (GetMassInVolume() > MassToOpenDoor)
  {
    OnOpen.Broadcast();
  }
  else
  {
    OnClose.Broadcast();
  }
}

float UDoor::GetMassInVolume()
{
  float Mass = 0.0f;

  // Find all the overlapping actors
  TArray<AActor*> ActorsInVolume;
  if (!VolumeToOpenDoor) { return Mass; }
  VolumeToOpenDoor->GetOverlappingActors(ActorsInVolume);
  // Iterate through them adding their masses
  for (const auto* Actor : ActorsInVolume)
  {
    Mass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    //UE_LOG(LogTemp, Warning, TEXT("%s is in trigger volume"), *Actor->GetName());
  }
  UE_LOG(LogTemp, Warning, TEXT("%f is in trigger volume"), Mass);
  return Mass;
}
