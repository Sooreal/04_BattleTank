// Copyright Sooreal

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float Throw); //Throw is how far the stick is pressed 

		UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurnRight(float Throw); //Throw is how far the stick is pressed 

		UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet); //it is public because we need to call it from the Blueprint

private:
		//Called from the pathfinding logic by the AI controllers
		virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};
