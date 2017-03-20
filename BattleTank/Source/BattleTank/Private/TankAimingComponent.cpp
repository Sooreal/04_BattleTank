// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO should this tick?

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; };

	//TankAimingcomponent is sufficient as WorldContextObject
	FVector OutLaunchVelocity; //TossVelocity is an OUT parameter
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //WE MAKE A SOCKET ON THE BARREL...and reference it directly (if it fails it returns the location of the Barrel)

	//calculate the OutLaunchVelocity
		if( UGameplayStatics::SuggestProjectileVelocity(
					this, //TankAimingcomponent is sufficient as WorldContextObject
					OutLaunchVelocity,//TossVelocity is an OUT parameter
					StartLocation, //WE MAKE A SOCKET ON THE BARREL...and reference it directly (if it fails it returns the location of the Barrel)
					HitLocation, //this is the end location
					LaunchSpeed, //the speed is the main variable that is used to calculate the arc, hence the direction	
					false,
					0,
					0,
					ESuggestProjVelocityTraceOption::DoNotTrace	//Parameter must be present to prevent bug
					) 
			)
		{ 
			auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //Unitize

			MoveBarrelTowards(AimDirection);

			auto Time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Warning, TEXT("%f: aim solution founf"), Time);

			//auto TankName = GetOwner()->GetName();
			//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"),*TankName, *Aimdirection.ToString());
			/*auto OurTankName = GetOwner()->GetName();
			auto BarrelLocation = Barrel->GetComponentLocation();
			UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());*/
		}
		else
		{
			auto Time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found."), Time);
		}
		


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Work out difference between the current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //this is the X Direction and we get three rotations in a single struct
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s "), *DeltaRotator.ToString());

	Barrel->Elevate(5);
	
}

