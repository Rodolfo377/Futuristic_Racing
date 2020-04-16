// Fill out your copyright notice in the Description page of Project Settings.


#include "ACO_Hover.h"
#include "Components/StaticMeshComponent.h"
#include "CustomCar.h"
#include "Engine/World.h"
#include "Engine/Canvas.h"

// Sets default values for this component's properties
UACO_Hover::UACO_Hover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UACO_Hover::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	FlyingCar = (ACustomCar*)Owner;

	
	SetupInputComponent();
	
}

// Called every frame
void UACO_Hover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ApplyCustomGravity();
	// ...
}

void UACO_Hover::SetupInputComponent()
{
	InputComponent = Owner->FindComponentByClass<UInputComponent>();
	
}




void UACO_Hover::PIDControl()
{
	double deltaTime = GetWorld()->DeltaTimeSeconds*1000;

	if (deltaTime >= TimeSample)
	{
		double currentError = Setpoint - CurrentVehicleHeight;
		TotalError += currentError;
		if (TotalError >= MaxControl)
		{
			TotalError = MaxControl;
		}
		else if (TotalError <= MinControl)
		{
			TotalError = MinControl;
		}

		double deltaError = currentError - LastError;
		ControlSignal = Kp * currentError + (Ki*TimeSample)*TotalError + (Kd / TimeSample)*deltaError;
		if (ControlSignal >= MaxControl)
		{
			ControlSignal = MaxControl;
		}
		else if (ControlSignal <= MinControl)
		{
			ControlSignal = MinControl;
		}
		//TODO: Draw Graph for P, I, D and Control Signal.

		LastError = currentError;		
	}
}

void UACO_Hover::ApplyHoverForce()
{
	PIDControl();	
	//local variable for adjusting the force of the thruster for the hovering
	double forcePercent = ControlSignal;

	FHitResult Hit = RaycastToFloor();
	FVector groundNormal;
	if (Hit.bBlockingHit)//if hit ground
	{
		CurrentVehicleHeight = Hit.Distance;
		groundNormal = Hit.Normal;
	
		FVector totalHoverForce = groundNormal * (HoverForceAmount) * forcePercent;
		//UE_LOG(LogTemp, Warning, TEXT("upwards force: (%f, %f, %f)"), totalHoverForce.X, totalHoverForce.Y, totalHoverForce.Z);
		//Apply hover force
		FlyingCar->ShipCore->AddForce(totalHoverForce);
	}
	
}

void UACO_Hover::ApplyCustomGravity()
{
	//TODO: Save hit info on class member variable 
	FHitResult Hit = RaycastToFloor();

	FVector p1 = GetReachLineStart();
	FVector p2 = GetReachLineEnd();
	DrawDebugLine(GetWorld(), p1, p2, FColor::Magenta);

	if (Hit.Actor->IsValidLowLevel())
	{
		FVector groundNormal;
		if (Hit.Actor->ActorHasTag("Track"))//if hit ground
		{
			//Apply custom gravity
			groundNormal = Hit.Normal;
			FVector downwardsForce = (-1)*groundNormal * HoverGravity * CurrentVehicleHeight;
			
			CustomGravityMagnitude = downwardsForce.Size();

			ApplyHoverForce();
			FlyingCar->ShipCore->AddForce(downwardsForce);
			AlignShipTrack(groundNormal);
			DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(50, 50, 50), FColor::Green, false, 0, 0, 3);
		}
		else
		{
			DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(50, 50, 50), FColor::Magenta, false, 0, 0, 3);
			UE_LOG(LogTemp, Warning, TEXT("Hit actor name: %s"), *Hit.Actor->GetName())
		}
	}
	else//flying
	{
		//Apply gravity downwards
		UE_LOG(LogTemp, Warning, TEXT("Flying"));
		UE_LOG(LogTemp, Warning, TEXT("fall gravity force: %f)"), -FallGravity);
		FlyingCar->ShipCore->AddForce(FVector(0, 0, -FallGravity));
		//align vehicle's up with world up
		FVector worldUpCross = FVector::CrossProduct(FlyingCar->GetActorUpVector(), FVector(0, 0, 1));
		FlyingCar->ShipCore->AddTorque(worldUpCross*TorqueAlignScale*TorqueRollAdjust);

	}
	
}

void UACO_Hover::AlignShipTrack(FVector groundNormal)
{
		FVector upVector = FlyingCar->GetActorUpVector();
		FVector fwdVector = FlyingCar->GetActorForwardVector();
		FVector projectionOnTrack;
		if (groundNormal.Size() != 0)
		{
			projectionOnTrack = fwdVector - (FVector::DotProduct(fwdVector, groundNormal)) / (pow(groundNormal.Size(), 2))*groundNormal;

			FVector newUpVector = groundNormal;
			FVector newFwdVector = projectionOnTrack;

			FVector fwdRot = FVector::CrossProduct(fwdVector, newFwdVector);
			FVector upRot = FVector::CrossProduct(upVector, newUpVector);


			FlyingCar->ShipCore->AddTorque(fwdRot*TorqueAlignScale*TorquePitchAdjust);
			FlyingCar->ShipCore->AddTorque(upRot*TorqueAlignScale*TorqueRollAdjust);
			
		}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Avoided division by zero error!"));
		return;
	}
}

FVector  UACO_Hover::GetReachLineStart()
{
	FVector PlayerPosition;
	FRotator PlayerRotation;
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerPosition, OUT PlayerRotation);
	PlayerPosition = FlyingCar->GetActorLocation();


	return PlayerPosition;
}

FVector  UACO_Hover::GetReachLineEnd()
{
	FVector PlayerPosition;
	FRotator PlayerRotation;
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerPosition, OUT PlayerRotation);
	PlayerPosition = FlyingCar->GetActorLocation();

	return PlayerPosition - FlyingCar->GetActorUpVector()*RaycastReach;
}

FHitResult UACO_Hover::RaycastToFloor()
{
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, FlyingCar);

	FVector p1 = GetReachLineStart();
	FVector p2 = GetReachLineEnd();

	

	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		hit,
		p1,
		p2,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TraceParams);

	

	return hit;
}


