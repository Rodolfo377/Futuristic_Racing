// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/GameInfo/TimeTrialRanking.h"
#include "../../Public/ActorComponents/ACO_SaveGameData.h"
#include "../../Public/ActorComponents/ACO_TimeKeeper.h"
#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/GameInfo/TimeTrialRanking.h"
#include "../../RacingGame.h"


// Sets default values for this component's properties
UACO_SaveGameData::UACO_SaveGameData()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
	// ...
}


// Called when the game starts
void UACO_SaveGameData::BeginPlay()
{
	Super::BeginPlay();
	Owner = (ACustomCar*)GetOwner();

	ensureAlways(Owner);
	// ...
	
}


// Called every frame
void UACO_SaveGameData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACO_SaveGameData::SaveGameData()
{
	class UTimeTrialRanking* SaveGameInstance = Cast<UTimeTrialRanking>(UGameplayStatics::CreateSaveGameObject(UTimeTrialRanking::StaticClass()));
	if (SaveGameInstance->IsValidLowLevel())
	{
		
		//Write Data on the savegame object
		//SaveGameInstance->AddEntry(Owner->RacerName, Owner->CarTimeKeeper->GetAllLapTimes(), FDateTime::Now());
		//
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex))
		{
			//Save succeeded.
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString(TEXT("Game Saved")), true);
		}
	}
}

void UACO_SaveGameData::LoadGameData()
{
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
}







