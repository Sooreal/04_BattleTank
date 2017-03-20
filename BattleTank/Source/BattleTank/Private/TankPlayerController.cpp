// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	//WE ALWAYS WANT TO START WITH Super - the boilerplate code does it always
	//SUPER means call the default behaviour before doing anything else
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller begin play."));

	auto controlledtank = GetControlledTank();

	if(controlledtank)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("We have our tank. %s"), *(controlledtank->GetName()));
	}
	else
	{ 
		UE_LOG(LogTemp, Warning, TEXT("No tank possessed."));
	}

}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();
	
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }

	//Get world location if you linetrace through the Crosshair 
	FVector HitLocation;
	

	//If it hits the landscape 
		if (GetSightRayHitLocation(HitLocation))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

			//Tell the controlled tank to aim at this point
			GetControlledTank()->AimAt(HitLocation);
		}
		
}

//True if it hits the Landscape - returns that location 
bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{	
	// Find the Crosshair position in pixel coordinates
		int32 ViewportSizeX, ViewportSizeY;
		GetViewportSize(ViewportSizeX, ViewportSizeY);

		auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

		//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());

	//De-project screen position of the crosshair to the world direction
		FVector LookDirection;
		if(GetLookDirection(ScreenLocation, LookDirection))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());

			//Line trace along that direction and see what we hit (up to some maximum range)
			GetLookVectorHitLocation(LookDirection, HitLocation);
				
		}	

		return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;	

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	
}


ATank* ATankPlayerController::GetControlledTank() const
{	
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const  
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); //one of many many ways of finding the camera location
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange); //self-explanatory

	if ( GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)) //HIT ANYTHING THAT IS VISIBLE
	{
			//Set Hit Location
			
			HitLocation = HitResult.Location;

			return true;
	}

	HitLocation = FVector(0);
	return false;
}





