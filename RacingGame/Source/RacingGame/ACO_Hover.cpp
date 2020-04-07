// Fill out your copyright notice in the Description page of Project Settings.


#include "ACO_Hover.h"
#include "Components/StaticMeshComponent.h"
#include "CustomCar.h"
#include "Engine/World.h"


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
	SetupPhysicsHandle();	
}

// Called every frame
void UACO_Hover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ApplyHoverForce();
	ApplyCustomGravity();
	// ...
}

void UACO_Hover::SetupInputComponent()
{
	InputComponent = Owner->FindComponentByClass<UInputComponent>();
	
}

void UACO_Hover::SetupPhysicsHandle()
{
	PhysicsHandle = Owner->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("At Object: %s Physics Handle component missing."), *GetOwner()->GetName());
	}
}



void UACO_Hover::PIDControl()
{
	double deltaTime = GetWorld()->DeltaTimeSeconds*1000;
	UE_LOG(LogTemp, Warning, TEXT("deltaTime: %f"), deltaTime)

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

		UE_LOG(LogTemp, Warning, TEXT("Control Signal: %f"), ControlSignal)
		UE_LOG(LogTemp, Warning, TEXT("Current error: %f"), currentError)

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
	
		FVector totalHoverForce = groundNormal * HoverForceAmount * forcePercent;
		//UE_LOG(LogTemp, Warning, TEXT("upwards force: (%f, %f, %f)"), totalHoverForce.X, totalHoverForce.Y, totalHoverForce.Z);
		//Apply hover force
		FlyingCar->ShipBody->AddForce(totalHoverForce);
	}
	AlignShipTrack(groundNormal);
}

void UACO_Hover::ApplyCustomGravity()
{
	//TODO: Save hit info on class member variable 
	FHitResult Hit = RaycastToFloor();
	FVector groundNormal;
	if (Hit.bBlockingHit)//if hit ground
	{			
		//Apply custom gravity
		groundNormal = Hit.Normal;
		FVector downwardsForce = (-1)*groundNormal * HoverGravity * CurrentVehicleHeight;
		UE_LOG(LogTemp, Warning, TEXT("downwards force: (%f, %f, %f)"), downwardsForce.X, downwardsForce.Y, downwardsForce.Z);
		FlyingCar->ShipBody->AddForce(downwardsForce);
	}
	else//flying
	{
		//Apply gravity downwards
		UE_LOG(LogTemp, Warning, TEXT("Flying"));
		UE_LOG(LogTemp, Warning, TEXT("fall gravity force: %f)"), -FallGravity);
		FlyingCar->ShipBody->AddForce(FVector(0, 0, -FallGravity));
	}
}

void UACO_Hover::AlignShipTrack(FVector groundNormal)
{
		/*FVector projectionOnTrack = FlyingCar->GetActorForwardVector() - groundNormal;
		FVector rightVector = FVector::CrossProduct(projectionOnTrack, groundNormal);
		FVector forwardVector = FVector::CrossProduct(rightVector, groundNormal);
		FVector upVector = groundNormal;*/
	

		FVector upVector = FlyingCar->GetActorUpVector();
		FVector fwdVector = FlyingCar->GetActorForwardVector();
		FVector projectionOnTrack;
		if (groundNormal.Size() != 0)
		{
				projectionOnTrack = fwdVector - (FVector::DotProduct(fwdVector, groundNormal)) / (pow(groundNormal.Size(), 2))*groundNormal;
	

		UE_LOG(LogTemp, Warning, TEXT("Current vehicle height: %f"), CurrentVehicleHeight)

		FHitResult Hit = RaycastToFloor();
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: (%f, %f, %f)"), Hit.Location.X, Hit.Location.Y, Hit.Location.Z)
		//hitpoint
		//FVector StartLine = FlyingCar->GetActorLocation() - FlyingCar->GetActorUpVector()*CurrentVehicleHeight;
		FVector StartLine = Hit.Location;
		FVector EndLine = StartLine + projectionOnTrack*100;

		//DrawDebugLine(GetWorld(), StartLine, EndLine, FColor::Cyan, false, 0, 0, 50.0);

		FVector StartShip = FlyingCar->GetActorLocation();

		FVector drawFwdShipOld = StartShip + fwdVector * 300;
		FVector drawFwdShipNew = StartShip + projectionOnTrack * 300;	

		FVector newUpVector = groundNormal;
		FVector newFwdVector = projectionOnTrack;

		FVector fwdRot = FVector::CrossProduct(fwdVector, newFwdVector);
		FVector upRot = FVector::CrossProduct(upVector, newUpVector);

		DrawDebugLine(GetWorld(), StartShip, drawFwdShipOld, FColor::Blue, false, 0, 0, 5.0);
		DrawDebugLine(GetWorld(), StartShip, drawFwdShipNew, FColor::Yellow, false, 0, 0, 5.0);
		DrawDebugLine(GetWorld(), StartShip, (StartShip + fwdRot*5000), FColor::Green, false, 0, 0, 5.0);
	


		UE_LOG(LogTemp, Warning, TEXT("crossProduct (%f, %f, %f)"), fwdRot.X, fwdRot.Y, fwdRot.Z);

		FlyingCar->ShipBody->AddTorque(fwdRot*TorqueAlignScale*TorquePitchAdjust);
		FlyingCar->ShipBody->AddTorque(upRot*TorqueAlignScale*TorqueRollAdjust);
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

	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		p1,
		p2,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TraceParams);
	//DrawDebugLine(GetWorld(), p1, p2, FColor::Red, false, 0, 0, 10.0f);
	/*if(!Hit.IsValidBlockingHit())
		UE_LOG(LogTemp, Error, TEXT("Hit not valid"))*/

	return Hit;
}


