// Fill out your copyright notice in the Description page of Project Settings.


#include "ACO_CollidingCarMovement.h"
#include "CustomCar.h"


UACO_CollidingCarMovement::UACO_CollidingCarMovement()
{
	FlyingCar = (ACustomCar*)GetOwner();
}


void UACO_CollidingCarMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	

	//checking all the necessary variables are still valid
	if (!FlyingCar || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		UE_LOG(LogTemp, Warning, TEXT("Colliding car movement RETURN"));
		return;
	}

	//get and clear the movement vector
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f)*FlyingCar->CurrentVelocity;
	/*UE_LOG(LogTemp, Warning, TEXT("desired movement this frame: (%f, %f, %f)"),
		DesiredMovementThisFrame.X,
		DesiredMovementThisFrame.Y,
		DesiredMovementThisFrame.Z);*/

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			UE_LOG(LogTemp, Warning, TEXT("Sliding along surface"));
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}
