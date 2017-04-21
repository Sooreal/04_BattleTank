// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:

	//How close can the AI tank get to the player	

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 8000;

private:		

		void BeginPlay() override;	
		

		virtual void Tick(float DeltaTime) override; //again we write virtual in front, just to remind us it is virtual and if you want to have children that inherit it, but is not neccessary

		
		
		
};
