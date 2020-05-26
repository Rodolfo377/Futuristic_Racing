// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACO_CarCollision.generated.h"

class UCapsuleComponent;
class ACustomCar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UACO_CarCollision : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_CarCollision();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void ResetPhysXParameters();

	ACustomCar* Owner = nullptr;

	UCapsuleComponent *CapsuleCollider = nullptr;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	

		
};
