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
class UACO_TimeKeeper;
class UACO_SaveGameData;

UCLASS()
class RACINGGAME_API ACustomCar : public APawn
{
	GENERATED_BODY()

///Functions
public:
	// Sets default values for this pawn's properties
	ACustomCar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void Hovering();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		int GetCurrentLap();
	UFUNCTION(BlueprintCallable)
		//get current "speed" of this car instance
		int GetCurrentVelocity();
	UFUNCTION(BlueprintCallable)
		int GetCurrentEnergyLevel() { return CurrentEnergyLevel; }
	UFUNCTION(BlueprintCallable)
		int GetMaxEnergyLevel() { return MaxEnergyLevel; }
	UFUNCTION(BlueprintCallable)
		void SetCurrentEnergyLevel(int energyLevel) { CurrentEnergyLevel = energyLevel; }
	UFUNCTION(BlueprintCallable)
		int GetWallHitDamage() { return WallHitDamage; }

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetCenterOfMass();

///Variables
public:
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

	//Component that will handle input-based movement: acceleration, steering, side friction. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACO_CarEngine *CarEngine = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACO_CarCollision *CarCollisionManager = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACO_TimeKeeper *CarTimeKeeper = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACO_SaveGameData *GameSaveComponent = nullptr;
	//Measured in m/s (x10 for aesthetics - big speed numbers on screen woo)
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	int CurrentVelocity = 0;

	UPROPERTY(EditAnywhere, Category = "Scoring")
		FString RacerName = "Bob";
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int MaxEnergyLevel = 100;
	const int MaxEnergyLevel2 = MaxEnergyLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int CurrentEnergyLevel = MaxEnergyLevel2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float WallHitDamage = 10;
	//How far below is the center of mass from the ship core mesh? (cm)
	UPROPERTY(EditAnywhere, Category = "Vehicle-Track Alignment")
		int CenterOfMassOffset = 200;

};
