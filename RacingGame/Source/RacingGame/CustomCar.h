// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CustomCar.generated.h"


class USphereComponent;

UCLASS()
class RACINGGAME_API ACustomCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomCar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Raycast to the floor to apply thrusters
	FHitResult RaycastToFloor();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* OurVisibleComponent;

	USphereComponent* SphereComponent;
	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

	UPROPERTY(EditAnywhere)
		float UpwardsForce = 0;
		
	UPROPERTY(EditAnywhere)
		float RaycastReach = 50;

	FVector CurrentVelocity;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	FVector GetReachLineStart();
	FVector GetReachLineEnd();

};
