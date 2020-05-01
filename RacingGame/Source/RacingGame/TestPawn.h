// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPawn.generated.h"

UCLASS()
class RACINGGAME_API ATestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestPawn();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ShipBody = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	class UACO_CollidingCarMovement* OurMovementComponent;
	UParticleSystemComponent* OurParticleSystem;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
	void MoveForward(float AxisValue);
	void Turn(float AxisValue);
	void ParticleToggle();
};
