// Copyright Sooreal

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::BeginPlay()
{
	//So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet)) { return; }
	Barrel = BarrelToSet;

	if (!ensure(TurretToSet)) { return; }
	Turret = TurretToSet;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(AimDirection, 0.01);
	
}

void UTankAimingComponent::AimAt(FVector HitLocation)
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
			AimDirection = OutLaunchVelocity.GetSafeNormal(); //Unitize

			MoveBarrelTowards(AimDirection);			

			//auto Time = GetWorld()->GetTimeSeconds();
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
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	//Work out difference between the current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //this is the X Direction and we get three rotations in a single struct
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s "), *DeltaRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("I am firing"));
	
	
	 
	if (FiringState != EFiringState::Reloading)
	{ 	//spawn the projectile at the end of the barrel

		if (!ensure(Barrel) ) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);

		//reset the fire time
		LastFireTime = FPlatformTime::Seconds();
	}


}



