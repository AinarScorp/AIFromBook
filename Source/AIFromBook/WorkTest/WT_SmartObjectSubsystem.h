// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WT_SmartObjectSubsystem.generated.h"

class ASmartCover;
class UCoverBillboardComponent;
/**
 * 
 */
UCLASS(DisplayName = "SmartObjectSubsystem")
class AIFROMBOOK_API UWT_SmartObjectSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
friend ASmartCover;
public:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	TArray<UCoverBillboardComponent*> GetCoverComponents();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UCoverBillboardComponent* GetCoverComponent(FVector Location);
public:
	UPROPERTY(BlueprintReadOnly)
	TMap<AActor*,UCoverBillboardComponent*> OccupyingActors;
private:
	UPROPERTY()
	TMap<FVector,UCoverBillboardComponent*> CoverComponents;

	
};
