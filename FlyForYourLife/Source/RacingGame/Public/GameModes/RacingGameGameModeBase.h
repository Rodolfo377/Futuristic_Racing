// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameGameModeBase.generated.h"

class ACustomCar;
class URaceInfo;
/**
 * 
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdate)

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
	//returns true if all the needed actors were initialized.
	UFUNCTION(BlueprintCallable)
	bool CheckLoadedActors();
	UFUNCTION(BlueprintCallable)
	void StartGame();
	UFUNCTION(BlueprintCallable)
	void PauseGame();
	UFUNCTION(BlueprintCallable)
	void QuitGame();
	UFUNCTION(BlueprintCallable)
	void CompleteGame();

	void Init();
	UFUNCTION(BlueprintCallable)
	void Update();

	UFUNCTION(BlueprintCallable)
	void AddTrackSpline(class USplineComponent* SplineComponent);

	UFUNCTION(BlueprintCallable)
	void AddCustomCar(ACustomCar* Vehicle);

	UFUNCTION(BlueprintCallable)
	void AddPlayerController(class ACarPlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void AddAIController(class AAICustomCar_Controller* AIController);

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

	//For now there is only one player, but adding an array of it will make it easier to implement multiplayer support. 
	TArray<class ACarPlayerController*> FAllPlayerControllers;
	TArray<class AAICustomCar_Controller*> FAllAIControllers;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool GameLoop = false;
};
