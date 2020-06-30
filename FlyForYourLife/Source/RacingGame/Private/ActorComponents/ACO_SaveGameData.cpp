// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/ActorComponents/ACO_SaveGameData.h"
#include "../../Public/GameInfo/TimeTrialRanking.h"
#include "../../Public/ActorComponents/ACO_TimeKeeper.h"
#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/GameInfo/TimeTrialRanking.h"
#include "../../RacingGame.h"
#include "Containers/Array.h"

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

void UACO_SaveGameData::Init()
{
	Owner = Cast<ACustomCar>(GetOwner());
	ensureAlways(Owner);
}

void UACO_SaveGameData::Update()
{
	if (SaveGameInstance && !SaveGameInstance->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Save Game bug occured!"));
	}
}




void UACO_SaveGameData::SaveGameData()
{
	//TODO: Create Save Game elsewhere. Perhaps make TimeTrialRAnking a singleton, or look for another option. 
	if (!SaveGameInstance)
	{
		SaveGameInstance = Cast<UTimeTrialRanking>(UGameplayStatics::CreateSaveGameObject(UTimeTrialRanking::StaticClass()));
	}
	if (SaveGameInstance)
	{
		//Write Data on the savegame object
		SaveGameInstance->AddEntry(Owner->RacerName, Owner->CarTimeKeeper->GetLastLapTime(), FDateTime::Now());
	
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex))
		{
			//Save succeeded.
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString(TEXT("Game Saved")), true);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error Saving Game!"));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString(TEXT("Error Saving Game!")), true);
	}
}

void UACO_SaveGameData::LoadGameData()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString(TEXT("Load Game")), true);
	class UTimeTrialRanking* LoadGameInstance = Cast<UTimeTrialRanking>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (LoadGameInstance->IsValidLowLevel())
	{
		FString lapTimes = "";

		for (auto entry : LoadGameInstance->BestLapTimes)
		{
			lapTimes = FString::SanitizeFloat(entry.lapTime);

			GEngine->AddOnScreenDebugMessage(-1,
				3.f,
				FColor::Green,
				FString("Game Saved: Player Name %s" + entry.PlayerName + " laptime: " + lapTimes),
				true);
		}
	}
}








