// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	//WE ALWAYS WANT TO START WITH Super - the boilerplate code does it always
	//SUPER means call the default behaviour before doing anything else
	Super::BeginPlay();	

	auto PlayerTank = GetPlayerTank();

	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player: %s"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller cannot find player tank."));
	}

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetPlayerTank())		
	{
		//Move towards the player

		//Aim towards the player
			GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//fire if we ready
	}
	

}

ATank* ATankAIController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) return nullptr;

	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::AimAtPlayer()
{
	if (!GetControlledTank()) { return; }
	
}



