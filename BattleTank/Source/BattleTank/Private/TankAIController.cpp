// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	//WE ALWAYS WANT TO START WITH Super - the boilerplate code does it always
	//SUPER means call the default behaviour before doing anything else
	Super::BeginPlay();	

	/*auto PlayerTank = GetPlayerTank();

	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player: %s"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller cannot find player tank."));
	}*/

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		//Get the player tank
		auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); //de-factored function
		auto ControlledTank = GetPawn();

		if (!ensure(PlayerTank && ControlledTank)) { return; }

		//Aim towards the player
			//Move towards the Player
			MoveToActor(PlayerTank,
				AcceptanceRadius //when the tank is as close as this they STOP - it is in CM						
				);

			//aim towards the player
			auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
			if (!ensure(AimingComponent)) { return; }
			AimingComponent->AimAt(PlayerTank->GetActorLocation());

			//Fire if we ready
			AimingComponent->Fire();
		

}





