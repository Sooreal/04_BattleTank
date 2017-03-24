// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //forward Declaration
class UTankAimingComponent;
class UTankMovementComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	

	UFUNCTION(BlueprintCallable, Category = Setup) //Category tells us in which BP category to put this function
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup) //Category tells us in which BP category to put this function
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable) //Category tells us in which BP category to put this function
		void Fire();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;	

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 10000; //TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
	
};
