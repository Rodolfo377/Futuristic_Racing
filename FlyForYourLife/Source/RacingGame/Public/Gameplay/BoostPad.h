// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostPad.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class RACINGGAME_API ABoostPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoostPad();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BoostPadMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	FName Tag = "Interest";

	//Indicates the closest waypoint, which will represent its location within the track.
	UPROPERTY(EditAnywhere)
	int WaypointId = 0;
};
