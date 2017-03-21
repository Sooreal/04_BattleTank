// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void  UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the barrel for the right amount this frame given a max elevation speed and the frame time

	//we also need to "clamp" the relative speed as well to -1 to +1
		RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange; //RelativeRotation is the property of the Scene Component

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees); //clamp the value

	SetRelativeRotation(FRotator(Elevation, 0, 0)); //passing it to the barrel..this is a constant rotation 	
}



