// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::ApplySidewaysForce()
{
	//Calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Work out the acceleration
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //apply oppsite of the slipping direction

																				 //Apply sideways F =ma
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //divide because there are two tracks

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Drive the tracks
		DriveTrack();
	//Apply sideways force
		ApplySidewaysForce();
	//reset Throttle
		CurrentThrottle = 0;

}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	//UE_LOG(LogTemp, Warning, TEXT("throttle: %f"), CurrentThrottle)
}

void UTankTrack::DriveTrack()
{
	//UE_LOG(LogTemp, Warning, TEXT("DrivingTrack"))

	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	/*IMPORTANT
	We go up to the class hierarchy to get to Tank_BP,
	but then we down to the Root component
	Then we cast that from the UStaticMeshComponent to the UPrimitiveComponent (up the hierarchy) - the simplest thing we can go to that has AddForceAtLocation*/
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //Owner is Tank_BP (self), its component is then Tank Component
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

