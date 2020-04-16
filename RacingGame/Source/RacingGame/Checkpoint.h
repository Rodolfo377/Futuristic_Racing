// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/Engine.h"
#include "Checkpoint.generated.h"

UCLASS()
class RACINGGAME_API ACheckpoint : public ATriggerVolume
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	//Each checkpoint is unique, remember to edit each instance so that it lies between and including 1 and 3.
	UPROPERTY(EditAnywhere)
	uint16 m_CheckpointId = 0;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
