// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/GameModes/RacingGameGameModeBase.h"
#include "../../Public/GameInfo/RaceInfo.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ARacingGameGameModeBase::BeginPlay()
{
	RaceInfo = Cast<URaceInfo>(GetComponentByClass(URaceInfo::StaticClass()));
	check(RaceInfo);
}

void ARacingGameGameModeBase::Tick(float DeltaTime)
{

}
