// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <vector>
#include "CustomCar.generated.h"


class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UACO_CarEngine;
class AStaticMeshActor;
class UACO_CarCollision;

UCLASS()
class RACINGGAME_API ACustomCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomCar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void Hovering();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Here the banking, tricks and other cosmetic transformations will be applied, without affecting the core movement of the ship
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ShipBody = nullptr;

	//Here the acceleration, steering and friction will be applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ShipCore = nullptr;

	//TODO change from TSoftObjectPtr to a static mesh actor, but retrieve wall collision mesh from game mode.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<AStaticMeshActor> WallCollisionMesh = nullptr;

	UPROPERTY(EditAnywhere)
		bool SideFrictionDraw = false;

	
	//Updates array of checkpoints completed when a custom car object overlaps with a checkpoint object. 
	//FIFO container.
	//@ id: unique id of checkpoint [1,3]
	void UpdateCheckpoint(uint32 checkpointId);



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
		int CurrentLap = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int MaxEnergyLevel = 100;
	const int MaxEnergyLevel2 = MaxEnergyLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int CurrentEnergyLevel = MaxEnergyLevel2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float WallHitDamage = 10;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	std::vector<int> Checkpoints = { 0 ,0 ,0 };
	
	//Component that will handle input-based movement: acceleration, steering, side friction. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACO_CarEngine *CarEngine = nullptr;
	UACO_CarCollision *CarCollisionManager = nullptr;
	//Measured in m/s (x10 for aesthetics - big speed numbers on screen woo)
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	int CurrentVelocity = 0;


	UFUNCTION()
		void OnHit(UPrimitiveComponent *HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComp,
			FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void NotifyHit(UPrimitiveComponent * MyComp,
			AActor * Other,
			class UPrimitiveComponent * OtherComp,
			bool bSelfMoved,
			FVector HitLocation,
			FVector HitNormal,
			FVector NormalImpulse,
			const FHitResult & Hit);

	//getters and setters
public:
	UFUNCTION(BlueprintCallable)
		int GetCurrentLap() { return CurrentLap; }
	UFUNCTION(BlueprintCallable)
		//get current "speed" of this car instance
		int GetCurrentVelocity();
	UFUNCTION(BlueprintCallable)
		int GetCurrentEnergyLevel() { return CurrentEnergyLevel; }
	UFUNCTION(BlueprintCallable)
		int GetMaxEnergyLevel() { return MaxEnergyLevel; }
	UFUNCTION(BlueprintCallable)
		void TakeWallDamage(int speedFactor);
};
