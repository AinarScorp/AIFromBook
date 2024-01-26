// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartCover.h"

#include "AIFromBook/WorkTest/CoverBillboardComponent.h"
#include "AIFromBook/WorkTest/WT_SmartObjectSubsystem.h"


FCoverInfo::FCoverInfo(AActor* Owner, const TSubclassOf<UCoverBillboardComponent> CompClass, const FName CompName, const FVector& SpawnOffset)
{
	BillboardComponent = NewObject<UCoverBillboardComponent>(Owner, CompClass.Get(), CompName);
	Owner->AddInstanceComponent(BillboardComponent);
	BillboardComponent->RegisterComponent();
	BillboardComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	BillboardComponent->SetRelativeLocation(SpawnOffset);
}

FCoverInfo::FCoverInfo(UCoverBillboardComponent* Component)
{
	BillboardComponent = Component;
}

FCoverInfo::~FCoverInfo()
{
	if (BillboardComponent)
	{
		//BillboardComponent->DestroyComponent();
	}
}

// Sets default values
ASmartCover::ASmartCover()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASmartCover::BeginPlay()
{
	Super::BeginPlay();
	//Add Cover Components To Subsystem
	UWT_SmartObjectSubsystem* SmartObjectSubsystem = GetGameInstance()->GetSubsystem<UWT_SmartObjectSubsystem>();
	for (auto CoverInfo : CoverInfos)
	{
		SmartObjectSubsystem->CoverComponents.Add(CoverInfo.BillboardComponent.Get()->GetComponentLocation(),CoverInfo.BillboardComponent.Get());
	}
}

void ASmartCover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASmartCover::AddCover()
{
	if (!CompClass) return;

	const FName Name = FName(*FString::Printf(TEXT("Billboard %i"), CoverInfos.Num()));
	CoverInfos.Add(FCoverInfo(this, CompClass, Name, CoverInfoSpawnOffset * (CoverInfos.Num() + 1)));
}

void ASmartCover::RemoveCover()
{
	if (CoverInfos.IsEmpty())
	{
		return;
	}
	if (CoverInfos[CoverInfos.Num() - 1].BillboardComponent)
	{
		CoverInfos[CoverInfos.Num() - 1].BillboardComponent->DestroyComponent();
	}
	CoverInfos.RemoveAt(CoverInfos.Num() - 1);
}

void ASmartCover::RemoveCover(UCoverBillboardComponent* CoverComp)
{
	for (int i = 0; i < CoverInfos.Num(); ++i)
	{
		if (CoverInfos[i].BillboardComponent != CoverComp) continue;
		CoverInfos[i].BillboardComponent->DestroyComponent();
		CoverInfos.RemoveAt(i);
		return;
	}
}

