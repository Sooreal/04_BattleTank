// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();

	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);

	//TODO clamp actual throttle value so player cannot over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	/*IMPORTANT
	  We go up to the class hierarchy to get to Tank_BP,
	  but then we down to the Root component
	  Then we cast that from the UStaticMeshComponent to the UPrimitiveComponent (up the hierarchy) - the simplest thing we can go to that has AddForceAtLocation*/
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //Owner is Tank_BP (self), its component is then Tank Component
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

