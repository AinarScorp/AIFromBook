// Fill out your copyright notice in the Description page of Project Settings.


#include "CoverBillboardComponent.h"

#include "WT_SmartObjectSubsystem.h"
#include "Cover/SmartCover.h"
#include "Kismet/KismetSystemLibrary.h"


UCoverBillboardComponent::UCoverBillboardComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

bool UCoverBillboardComponent::CanOccupyCover()
{
	return IsOccupied && OccupyingActor == nullptr;
}

bool UCoverBillboardComponent::TryOccupyCover(AActor* AttemptingToOccupyActor)
{
	if (IsOccupied && OccupyingActor != AttemptingToOccupyActor) return false;
	UWT_SmartObjectSubsystem* SmartObjectSubsystem = GetOwner()->GetGameInstance()->GetSubsystem<UWT_SmartObjectSubsystem>();
	if (SmartObjectSubsystem->OccupyingActors.Contains(AttemptingToOccupyActor))
	{
		SmartObjectSubsystem->OccupyingActors[AttemptingToOccupyActor]->StopOccupyingCover(AttemptingToOccupyActor);
	}
	
	SmartObjectSubsystem->OccupyingActors.Add(AttemptingToOccupyActor,this);
	IsOccupied = true;
	OccupyingActor = AttemptingToOccupyActor;
	return true;
}

void UCoverBillboardComponent::StopOccupyingCover(AActor* CurrentlyOccupyingActor)
{
	if (OccupyingActor != CurrentlyOccupyingActor) return;
	IsOccupied = false;
	OccupyingActor = nullptr;
}



void UCoverBillboardComponent::DrawGizmos_Implementation()
{
}


void UCoverBillboardComponent::BeginPlay()
{
	Super::BeginPlay();
	CalculateCoverDirection();
}

void UCoverBillboardComponent::RemoveCover()
{
	if (ASmartCover* SmartCover = Cast<ASmartCover>(GetOwner()))
	{
		SmartCover->RemoveCover(this);
	}
}

void UCoverBillboardComponent::CalculateCoverDirection()
{
	const TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(this,GetComponentLocation(),GetOwner()->GetActorLocation(),
		TraceTypeQuery1,false,ActorsToIgnore,EDrawDebugTrace::Type::None, HitResult,false);
	if (HitResult.GetActor() == GetOwner())
	{
		CoverDirection = FVector::VectorPlaneProject(HitResult.Normal, FVector::UpVector);
		CoverDirection.Normalize();
	}
}
