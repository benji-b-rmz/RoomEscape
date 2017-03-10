// Copyright Ben Ramirez 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Open the door
	void OpenDoor();
	void CloseDoor();

private:

	UPROPERTY(EditAnywhere)
	float OpenAngle = -90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;

	float LastDoorOpenTime;
	AActor* ActorThatOpens; // Remember pawn inherits from Actor
	AActor* Owner; // The owning  door

	//Returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
