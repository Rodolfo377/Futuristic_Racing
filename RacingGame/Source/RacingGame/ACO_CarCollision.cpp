// Fill out your copyright notice in the Description page of Project Settings.


#include "ACO_CarCollision.h"
#include "CustomCar.h"
#include "Components/CapsuleComponent.h"
/*#include "Physics/PhysicsInterfacePhysX.h"
#include "PhysicsEngine/BodyInstance.h"
#include "ThirdParty/PhysX3/PhysX_3.4/Include/PxShape.h"
#include "PhysicsCore/Public/PhysXPublicCore.h"
#include <PxScene.h>*/
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"

// Sets default values for this component's properties
UACO_CarCollision::UACO_CarCollision()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACO_CarCollision::BeginPlay()
{
	Super::BeginPlay();
	Owner = (ACustomCar*)GetOwner();
	ensureAlways(Owner);
	// ...
	
	/*CapsuleCollider = Owner->FindComponentByClass<UCapsuleComponent>();
	ensureAlways(CapsuleCollider);

	if (!CapsuleCollider->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Capsule Collider not valid"))
	}*/
	
}


// Called every frame
void UACO_CarCollision::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}



void UACO_CarCollision::ResetPhysXParameters()
{
	//ShipCore->Bodyin
	/*FPhysicsActorHandle *shipPhysicsActorHandle = &Owner->ShipCore->GetBodyInstance()->GetPhysicsActorHandle();
	ensureAlways(shipPhysicsActorHandle);

	PxScene *scene = shipPhysicsActorHandle->SyncActor->getScene();
	ensureAlways(scene);

	scene->lockWrite();

	//TArray<FPhysicsShapeHandle_PhysX> shipCollisionShapes;
	//
	//CapsuleCollider->BodyInstance.GetAllShapes_AssumesLocked(shipCollisionShapes);
	////Owner->ShipCore->BodyInstance.GetAllShapes_AssumesLocked(shipCollisionShapes);

	//if (shipCollisionShapes.Num() > 0)
	//{
	//	for (FPhysicsShapeHandle_PhysX var : shipCollisionShapes)
	//	{
	//		var.Shape->setRestOffset(1);
	//		var.Shape->setContactOffset(2);
	//	}
	//}
	//

	if (Owner->WallCollisionMesh->IsValidLowLevel())
	{
		//Owner->WallCollisionMesh-
		TArray<FPhysicsShapeHandle_PhysX> wallCollisionShapes;
		Owner->ShipCore->BodyInstance.GetAllShapes_AssumesLocked(wallCollisionShapes);

		if (wallCollisionShapes.Num() > 0)
		{
			for (FPhysicsShapeHandle_PhysX var : wallCollisionShapes)
			{
				var.Shape->setRestOffset(10);
				var.Shape->setContactOffset(20);
				
			}
		}
	}
	scene->unlockWrite();*/
}

