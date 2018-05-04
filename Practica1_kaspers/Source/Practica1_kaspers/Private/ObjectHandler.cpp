// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectHandler.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UObjectHandler::UObjectHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UObjectHandler::BeginPlay()
{
	Super::BeginPlay();
  FindPhysicsHandleComponent();
  SetupInputComponent();
}

// Called every frame
void UObjectHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (!PhysicsHandle) { return; }
  if (PhysicsHandle->GrabbedComponent)
  {
    // move the object that has been picked up
    PhysicsHandle->SetTargetLocation(GetLineEnd());
  }

  //--------------------------------------------------------------------------------------------------------------------------------------------
  if (ShowRayCastLine)
  {
    FVector LineTraceStart = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    FVector ForwardVector = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorForwardVector();
    FVector LineTraceEnd = LineTraceStart + ForwardVector * Distance;
    DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 1.0f);
  }
}

// Picks up whatever object is in reach of the Ray-cast 
void UObjectHandler::PickUp()
{
  UE_LOG(LogTemp, Warning, TEXT("PickUp pressed!"));

  // Ray-cast and see if there are any actors with physics body in range
  auto HitResult = GetFirstPhysicsBodyInRange();
  auto ComponentToPickUp = HitResult.GetComponent(); // gets the mesh
  auto ActorHit = HitResult.GetActor();

  // If there is something in range, then attach a physics handle
  if (ActorHit)
  {
    if (!PhysicsHandle) { return; }

    /*PhysicsHandle->GrabComponentAtLocation(
      ComponentToPickUp,
      NAME_None,
      ComponentToPickUp->GetOwner()->GetActorLocation()
    );*/

    PhysicsHandle->GrabComponent(
      ComponentToPickUp,
      NAME_None, // no need for bones
      ComponentToPickUp->GetOwner()->GetActorLocation(),
      false // allows rotation
    );

  }
}

// Lets go of the object that has been picked up
void UObjectHandler::LetGo()
{
  if (!PhysicsHandle) { return; }
  PhysicsHandle->ReleaseComponent();
}

// Finds physics handle component
void UObjectHandler::FindPhysicsHandleComponent()
{
  PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if (PhysicsHandle == nullptr)
  {
    UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component!"), *GetOwner()->GetName());
  }
}

// Sets up input component
void UObjectHandler::SetupInputComponent()
{
  InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
  if (InputComponent)
  {
    InputComponent->BindAction("PickUp", IE_Pressed, this, &UObjectHandler::PickUp);
    InputComponent->BindAction("PickUp", IE_Released, this, &UObjectHandler::LetGo);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("%s missing input component!"), *GetOwner()->GetName());
  }
}

// Returns the hit for the first physics body in range
FHitResult UObjectHandler::GetFirstPhysicsBodyInRange()
{
  // Ray-cast out to reach distance
  FHitResult HitResult;
  FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
  GetWorld()->LineTraceSingleByObjectType(
    HitResult,
    GetLineStart(),
    GetLineEnd(),
    FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
    TraceParameters
  );
  return HitResult;
}

// Returns the start of the line
FVector UObjectHandler::GetLineStart()
{
  /*FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
    PlayerViewPointLocation,
    PlayerViewPointRotation
  );*/
  FVector LineTraceStart = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
  return LineTraceStart;
}

// Returns the end of the line
FVector UObjectHandler::GetLineEnd()
{
  /*FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
    PlayerViewPointLocation,
    PlayerViewPointRotation
  );
  return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Distance);*/
  FVector ForwardVector = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorForwardVector();
  FVector LineTraceEnd = GetLineStart() + ForwardVector * Distance;
  return LineTraceEnd;
}

