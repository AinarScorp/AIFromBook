// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"

#include "CoverBillboardComponent.h"
#include "WT_SmartObjectSubsystem.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AShooter::AShooter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AShooter::StopOccupyingCover()
{
	if (!IsBehindCover) return;

	UWT_SmartObjectSubsystem* SmartObjectSubsystem =GetGameInstance()->GetSubsystem<UWT_SmartObjectSubsystem>();
	if (!SmartObjectSubsystem || !SmartObjectSubsystem->OccupyingActors.Contains(this)) return;

	SmartObjectSubsystem->OccupyingActors[this]->StopOccupyingCover(this);
}

void AShooter::SetIsBehindCover(bool NewIsBehindCover)
{
	CrouchLevel = IsBehindCover? 1.f:0.f;
	IsBehindCover = NewIsBehindCover;
	OnIsBehindCoverChanged.Broadcast(IsBehindCover);
	GetWorldTimerManager().SetTimer(CrouchLevelModificationTimer,this,&AShooter::ChangeCrouchLevel,GetWorld()->GetDeltaSeconds(),true);
}

void AShooter::ChangeCrouchLevel()
{
	const float NotClampedValue = FMath::FInterpTo(CrouchLevel,IsBehindCover?1:0,GetWorld()->GetDeltaSeconds(),10);
	CrouchLevel = FMath::Clamp(NotClampedValue, 0,1);
	if (CrouchLevel <0.01f || CrouchLevel>0.99f )
	{
		GetWorldTimerManager().ClearTimer(CrouchLevelModificationTimer);
	}
}
