// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Gameplay/Checkpoint.h"
#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/ActorComponents/ACO_TimeKeeper.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnActorBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACheckpoint::OnOverlapEnd);
}

void ACheckpoint::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
	ACustomCar* vehicle = Cast<ACustomCar>(OtherActor);
	ensureAlways(vehicle);
	ensureAlways(vehicle->CarTimeKeeper);

	vehicle->CarTimeKeeper->UpdateCheckpoint(m_CheckpointId);
}

void ACheckpoint::OnOverlapEnd(AActor * OverlappedActor, AActor * OtherActor)
{

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	if (m_CheckpointId == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("invalid checkpoint id! Insert a instance-unique value between 1-3"))
			return;
	}
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}



