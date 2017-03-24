// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Turret || !Barrel) { return; }	

	//TankAimingcomponent is sufficient as WorldContextObject
	FVector OutLaunchVelocity; //TossVelocity is an OUT parameter
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //WE MAKE A SOCKET ON THE BARREL...and reference it directly (if it fails it returns the location of the Barrel)

	//calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::OnlyTraceWhileAscending // Paramater must be present to prevent bug
	);



		if( bHaveAimSolution )
		{ 
			auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //Unitize

			MoveBarrelTowards(AimDirection);			

			auto Time = GetWorld()->GetTimeSeconds();
			//UE_LOG(LogTemp, Warning, TEXT("%f: aim solution found"), Time);

			//auto TankName = GetOwner()->GetName();
			//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"),*TankName, *Aimdirection.ToString());
			/*auto OurTankName = GetOwner()->GetName();
			auto BarrelLocation = Barrel->GetComponentLocation();
			UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());*/
		}
		else
		{
			auto Time = GetWorld()->GetTimeSeconds();
			//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found."), Time);
		}
		


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{	

	//Work out difference between the current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //this is the X Direction and we get three rotations in a single struct
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s "), *DeltaRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}



