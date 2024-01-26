// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIFromBook/WorkTest/CoverBillboardComponent.h"
#include "GameFramework/Actor.h"
#include "SmartCover.generated.h"

class UCoverBillboardComponent;

USTRUCT(BlueprintType)
struct FCoverInfo
{
	GENERATED_BODY()
	FCoverInfo(){}
	explicit FCoverInfo(AActor* Owner,TSubclassOf<UCoverBillboardComponent> CompClass, FName CompName, const FVector& SpawnOffset);
	explicit FCoverInfo(UCoverBillboardComponent* Component);
	~FCoverInfo();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UCoverBillboardComponent> BillboardComponent;


};

UCLASS(HideCategories = (Replication,HLOD,Physics,Networking,Input,Actor,Cooking))
class AIFROMBOOK_API ASmartCover : public AActor
{
	GENERATED_BODY()

public:
	ASmartCover();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void RemoveCover(UCoverBillboardComponent* CoverComp);

private:
	UFUNCTION(CallInEditor,BlueprintCallable)
	void AddCover();
	UFUNCTION(CallInEditor,BlueprintCallable)
	void RemoveCover();

private:
	UPROPERTY(EditAnywhere,DisplayName = "Component Class")
	const TSubclassOf<UCoverBillboardComponent> CompClass;
	UPROPERTY(EditAnywhere)
	FVector CoverInfoSpawnOffset{0,0,100.f};
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FCoverInfo> CoverInfos;
	
};
