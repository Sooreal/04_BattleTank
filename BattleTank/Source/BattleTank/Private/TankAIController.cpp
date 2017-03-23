// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
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
		auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()); //de-factored function
		auto ControlledTank = Cast<ATank>(GetPawn());

		//Aim towards the player
		if(PlayerTank)
		{
			ControlledTank->AimAt(PlayerTank->GetActorLocation());		

			//Fire if we ready
				ControlledTank->Fire(); //TODO Do not fire every frame
		}	

}





