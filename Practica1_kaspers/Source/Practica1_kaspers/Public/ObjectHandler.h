// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "ObjectHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICA1_KASPERS_API UObjectHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

private:

  // Distance in front of the player
  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float Distance = 150.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Debug")
  bool ShowRayCastLine = false;

  UPhysicsHandleComponent* PhysicsHandle = nullptr;

  UInputComponent* InputComponent = nullptr;

  // Picks up whatever object is in reach of the Ray-cast 
  void PickUp();

  // Lets go of the object that has been picked up
  void LetGo();

  // Finds physics handle component
  void FindPhysicsHandleComponent();

  // Sets up input component
  void SetupInputComponent();

  // Returns the hit for the first physics body in range
  FHitResult GetFirstPhysicsBodyInRange();

  // Returns the start of the line
  FVector GetLineStart();

  // Returns the end of the line
  FVector GetLineEnd();
		
	
};
