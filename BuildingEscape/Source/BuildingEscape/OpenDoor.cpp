// Copyright Ben Ramirez 2017

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

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
	
	this->Owner = GetOwner();
	if (!PressurePlate) 
	{
		UE_LOG(LogTemp, Error, TEXT("SOMETHING MISSING PRESSURE PLATE"));
	}
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
	if (GetTotalMassOfActorsOnPlate() > 30.f) // TODO make into a parameter 
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	//Check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > this->DoorCloseDelay) {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//return total mass in kg
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("SUPPPP: %s"),*Actor->GetName());
	}
	return TotalMass;
}
