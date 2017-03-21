// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void  UTankTurret::Rotate(float RelativeSpeed)
{
	//Move the barrel for the right amount this frame given a max elevation speed and the frame time

	//we also need to "clamp" the relative speed as well to -1 to +1
	//RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewRotation = RelativeRotation.Yaw + RotationChange; //RelativeRotation is the property of the Scene Component	

	SetRelativeRotation(FRotator(0, RawNewRotation, 0)); //passing it to the barrel..this is a constant rotation 	
}




