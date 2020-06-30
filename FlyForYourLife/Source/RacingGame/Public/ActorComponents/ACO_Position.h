// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACO_Position.generated.h"

class USplineComponent;

USTRUCT(BlueprintType, Blueprintable)
struct FPositionStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float DistanceAlongTrack = 0;
	UPROPERTY(BlueprintReadWrite)
	int RacePosition = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RACINGGAME_API UACO_Position : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_Position();
	void Init();
	void Update();

	UFUNCTION(BlueprintCallable)
	FVector GetRespawnPoint();
	UFUNCTION(BlueprintCallable)
	float GetApproxDistanceClosestToWorldLocation(FVector Pos_WS, const USplineComponent* Spline);

protected:


public:	
	class ACustomCar* Owner = nullptr;
	FName TrackTag = "Track";
	AActor* Track = nullptr;
	class USplineComponent* Spline = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPositionStats PositionStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentWaypoint = 1;
private:
	class ARacingGameGameModeBase* GameMode = nullptr;
};
