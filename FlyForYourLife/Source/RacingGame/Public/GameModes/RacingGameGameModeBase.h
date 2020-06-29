// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameGameModeBase.generated.h"

class URaceInfo;
class ACustomCar;
/**
 * 
 */

USTRUCT(BlueprintType)
struct FWaypointInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TargetReachedRadius = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SteeringDetectionRadius = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector WorldPosition;
};

UCLASS()
class RACINGGAME_API ARacingGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void StartMode() {};
	virtual void PauseMode() {};
	virtual void QuitMode() {};
	virtual void CompleteMode() {};

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	//UPROPERTY(EditAnywhere)
	//URaceInfo *RaceInfo = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> WaypointPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Waypoints")
	TArray<FWaypointInfo> ArrayOfWaypoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ACustomCar*> AllCars;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugging")
	bool DrawDebugWaypoints = false;

	//Sort Vehicles by their current laps and progress within the race
	UFUNCTION(BlueprintCallable)
	void SortVehicles(TArray<ACustomCar*> AllVehicles);

	class URaceInfo* RaceInfo = nullptr;

	AActor* Track = nullptr;
	class USplineComponent* Spline = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InitFlag = false;

};
