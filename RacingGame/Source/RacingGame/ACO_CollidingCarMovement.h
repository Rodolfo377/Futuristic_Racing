// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ACO_CollidingCarMovement.generated.h"

/**
 * 
 */
class ACustomCar;

UCLASS()
class RACINGGAME_API UACO_CollidingCarMovement : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	UACO_CollidingCarMovement();
	ACustomCar* FlyingCar = nullptr;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
