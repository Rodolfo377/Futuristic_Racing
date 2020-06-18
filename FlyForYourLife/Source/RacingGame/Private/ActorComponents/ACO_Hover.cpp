// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/ActorComponents/ACO_Hover.h"
#include "Components/StaticMeshComponent.h"
#include "../../Public/Pawns/CustomCar.h"
#include "Engine/World.h"
#include "Engine/Canvas.h"
#include "Materials/MaterialInstance.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"

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
	Owner = (ACustomCar*)GetOwner();

	ensureAlways(Owner);
	SetupInputComponent();
	

}

void UACO_Hover::DebugDraw()
{
	if (DebugDrawCenterOfMass)
	{
		DrawDebugSphere(GetWorld(), Owner->GetActorLocation() + Owner->GetActorUpVector()*CenterOfMassOffset, 100, 12, FColor::Cyan,
			false, 0, 0, 5);
	}
}

void UACO_Hover::SetCenterOfMass()
{
	Owner->ShipCore->SetCenterOfMass(-Owner->GetActorUpVector()*CenterOfMassOffset);
}

// Called every frame
void UACO_Hover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ApplyCustomGravity();
}

void UACO_Hover::SetupInputComponent()
{
	InputComponent = Owner->FindComponentByClass<UInputComponent>();
}

//Second Implementation: 16/04/2020
void UACO_Hover::PIDControl()
{
	float deltaTime = GetWorld()->DeltaTimeSeconds;
	float proportional = Setpoint - CurrentVehicleHeight;

	float derivative = (proportional - lastProportional) / deltaTime;
	integral += proportional * deltaTime;
	lastProportional = proportional;

	ControlSignal = Kp * proportional + Ki * integral + Kd * derivative;
	ControlSignal = FMath::Clamp(ControlSignal, MinControl, MaxControl);
}

void UACO_Hover::ApplyHoverForce()
{
	PIDControl();
	//local variable for adjusting the force of the thruster for the hovering
	double forcePercent = ControlSignal;

	FHitResult Hit = RaycastToFloor(FVector(0, 0, 0));
	FVector groundNormal;
	if (Hit.bBlockingHit)//if hit ground
	{
		CurrentVehicleHeight = Hit.Distance;
		groundNormal = Hit.Normal;

		FVector totalHoverForce = groundNormal * (HoverForceAmount)* forcePercent;

		//Apply hover force
		Owner->ShipCore->AddForce(totalHoverForce);
	}
}

void UACO_Hover::ApplyCustomGravity()
{
	//TODO: Save hit info on class member variable 
	FHitResult Hit = RaycastToFloor(FVector(0, 0, 0));

	FVector p1 = GetReachLineStart(FVector(0, 0, 0));
	FVector p2 = GetReachLineEnd(p1);

	/*DrawDebugSphere(GetWorld(), p1, 10, 10, FColor::White);
	DrawDebugSphere(GetWorld(), p2, 10, 10, FColor::Blue);*/

	if (Hit.Actor->IsValidLowLevel())
	{
		FVector groundNormal;		
		
		if (Hit.Actor->ActorHasTag("Track"))//if hit ground
		{
				//Apply custom gravity
				groundNormal = Hit.Normal;
				downwardsForce = (-1)*groundNormal * HoverGravity;
				TempGroundNormal = groundNormal;
				ApplyHoverForce();
				Owner->ShipCore->AddForce(downwardsForce);
				AlignShipTrack();
				//DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(50, 50, 50), FColor::Green, false, 0, 0, 3);
		}
		else
		{
				//apply custom gravity in the last known downwards direction
			Owner->ShipCore->AddForce(downwardsForce * 1000);
		
		}
		
	}
	else//flying
	{
		Owner->ShipCore->AddForce(FVector(0, 0, -FallGravity));
		//Apply gravity downwards
		//Owner->ShipCore->AddForce(FVector(0, 0, -FallGravity));
		//align vehicle's up with world up
		FVector worldUpCross = FVector::CrossProduct(Owner->GetActorUpVector(), FVector(0, 0, 1));
		Owner->ShipCore->AddTorqueInRadians(worldUpCross*TorqueAlignScale*TorqueRollAdjust);

	}

}

void UACO_Hover::AlignShipTrack()
{
	FVector velocity = Owner->GetVelocity();
	FVector p1 = GetReachLineStart(FVector(0, 0, 0));
	FVector p2 = GetReachLineEnd(p1);

	FHitResult Hit = RaycastToFloor(FVector(0, 0, 0));
	FVector upVector = Owner->GetActorUpVector();
	FVector fwdVector = Owner->GetActorForwardVector();
	FVector projectionOnTrack;

	FVector groundNormal = Hit.Normal;
	FVector copiedNormal = TempGroundNormal;

	if (groundNormal.Size() != 0)
	{
		projectionOnTrack = fwdVector - (FVector::DotProduct(fwdVector, groundNormal)) / (pow(groundNormal.Size(), 2))*groundNormal;

		FVector newUpVector = groundNormal;
		FVector newFwdVector = projectionOnTrack;

		FVector fwdRot = FVector::CrossProduct(fwdVector, newFwdVector);
		FVector upRot = FVector::CrossProduct(upVector, newUpVector);

		Owner->ShipCore->AddTorqueInRadians(fwdRot*TorqueAlignScale*TorquePitchAdjust);
		Owner->ShipCore->AddTorqueInRadians(upRot*TorqueAlignScale*TorqueRollAdjust);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Avoided division by zero error!"));
		return;
	}
}

FVector  UACO_Hover::GetReachLineStart(FVector offset)
{
	FVector PlayerPosition;
	FRotator PlayerRotation;
	PlayerPosition = Owner->GetActorLocation() + offset;

	return PlayerPosition;
}

FVector  UACO_Hover::GetReachLineEnd(FVector startPos)
{
	FVector PlayerPosition;
	FRotator PlayerRotation;

	return startPos - Owner->GetActorUpVector()*RaycastReach;
}

FHitResult UACO_Hover::RaycastToFloor(FVector offset)
{
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, Owner);

	FHitResult closestHit;
	closestHit.Distance = -1;

	FHitResult allHits[4];
	FVector origin = GetReachLineStart(offset);

	FVector allFloorWhiskers[] = 
	{(origin + (-Owner->GetActorUpVector() + Owner->GetActorForwardVector()) * GravityRaycastReach),
	(origin + (-Owner->GetActorUpVector() - Owner->GetActorForwardVector() + Owner->GetActorRightVector()) * GravityRaycastReach),
	(origin + (-Owner->GetActorUpVector() - Owner->GetActorForwardVector() - Owner->GetActorRightVector()) * GravityRaycastReach),
	(origin + (Owner->GetActorUpVector()) * GravityRaycastReach)
	};

	for (int i = 0; i < 4; i++)
	{
		//DrawDebugLine(GetWorld(), origin, allFloorWhiskers[i], FColor::Purple);


		GetWorld()->LineTraceSingleByObjectType(
			allHits[i],
			origin,
			allFloorWhiskers[i],
			FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
			TraceParams);
	}


	for (int i = 0; i < 4; i++)
	{
		if (allHits[i].IsValidBlockingHit())
		{
			if (closestHit.Distance < 0)//set the closest distance to the first valid value
			{
				closestHit = allHits[i];
			}
			else if (allHits[i].Distance < closestHit.Distance)
			{
				closestHit = allHits[i];
			}
		}
	}
	/*if (closestHit.IsValidBlockingHit())
	{
		if (GetHitMaterial(closestHit))
		{
			if (GetHitMaterial(closestHit)->GetName() == "Dirt")
			{
				UE_LOG(LogTemp, Warning, TEXT("Hey! this is dirt!"));
			}
		}
	}*/
	return closestHit;
}

/*UPhysicalMaterial* UACO_Hover::GetHitMaterial(FHitResult hit)
{
	UStaticMeshComponent* ActorMesh = Cast<UStaticMeshComponent>(hit.Actor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	verifyf(ActorMesh, TEXT("No Actor Mesh Detected %s"), *hit.Actor->GetName());

	UPhysicalMaterial* physMat = nullptr;
	if(ActorMesh->GetStaticMesh()->IsValidLowLevel())
	physMat = ActorMesh->GetStaticMesh()->GetMaterial(0)->GetPhysicalMaterial();

	return physMat;
}*/


