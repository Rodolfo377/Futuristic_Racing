// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

//Headers for Custom Save System
#include "Archive.h"
#include "BufferArchive.h"
#include "FileManager.h"
#include "FileHelper.h"
#include "MemoryReader.h"

#include "ACO_SaveGameData.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UACO_SaveGameData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACO_SaveGameData();
	void Init();
	void Update();

	UFUNCTION()
	void SaveGameData();
	
	UFUNCTION()
	void LoadGameData();

protected:

	//member variables
public:
	class ACustomCar *Owner = nullptr;
	class UTimeTrialRanking* SaveGameInstance = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;
};
