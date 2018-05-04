// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICA1_KASPERS_API UDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  UPROPERTY(BlueprintAssignable)
  FDoorEvent OnOpen;

  UPROPERTY(BlueprintAssignable)
  FDoorEvent OnClose;

private:

  UPROPERTY(EditAnywhere)
  ATriggerVolume* VolumeToOpenDoor = nullptr;

  UPROPERTY(EditAnywhere)
  float MassToOpenDoor = 250.0f;

  // Returns total mass
  float GetMassInVolume();
};
