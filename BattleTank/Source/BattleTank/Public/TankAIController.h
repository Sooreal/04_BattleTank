// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:		

		void BeginPlay() override;	
		

		virtual void Tick(float DeltaTime) override; //again we write virtual in front, just to remind us it is virtual and if you want to have children that inherit it, but is not neccessary

		//How close can the AI tank get to the player		
		float AcceptanceRadius = 300;
		
};
