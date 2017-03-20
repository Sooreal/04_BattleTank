// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

private:

		ATank* GetControlledTank() const;
	
	  virtual void BeginPlay() override; //override says :" pleas make sur there is a function exactly like this  up in the inheritance chain
								//it will find it in the AActor...where it is virtual void..low and behold		
								//virtual says :"my children are allowed to override this function"
								//if you do not know how to define the function, find it in the parent and copy it..

	  virtual void Tick(float DeltaTime) override; //again we write virtual in front, just to remind us it is virtual and if you want to have children that inherit it, but is not neccessary

	  //Start the tank moving the barrel so that the shot would hit where the crosshair intersects the world
	  void AimAtCrosshair(); //no const because it will change something about the state of the TankController

	//Return an OUT Parameter - true if it hits landscape
	  bool GetSightRayHitLocation(FVector& HitLocation) const;

	  UPROPERTY(EditAnywhere)
		  float CrosshairXLocation = 0.5;

	  UPROPERTY(EditAnywhere)
		  float CrosshairYLocation = 0.33333;

	  UPROPERTY(EditAnywhere)
		  float LineTraceRange = 1000000;

		  bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;	

		  bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

		
};
