// Copyright Ben Ramirez 2017

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	this->ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	this->Owner = GetOwner();
}


void UOpenDoor::OpenDoor() 
{
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor() 
{
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// poll the Trigger Volume every fram
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) 
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	// if the ActorThatOpens is in the volume

	//Check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > this->DoorCloseDelay) {
		CloseDoor();
	}
}

