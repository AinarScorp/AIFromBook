// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AS_MovementComponent.generated.h"

struct FKinematic
{
	FVector Position;
	float Orientation;
	FVector LinearVelocity;
	float AngularVelocity;

};

USTRUCT(BlueprintType)
struct FSteeringOutput
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FVector LinearVelocity;
	UPROPERTY(EditAnywhere)
	float AngularVelocity;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName ="BaseMovementComponent",
	HideCategories = (Replication, Collision,AssetUserData,Activation,Cooking,ComponentReplication,ComponentTick))
class AIFROMBOOK_API UAS_MovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAS_MovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	FSteeringOutput SteeringOutput;
	
	UPROPERTY(EditAnywhere)
	FVector Position;
	UPROPERTY(EditAnywhere)
	float Orientation;
	UPROPERTY(EditAnywhere)
	FVector LinearVelocity;
	UPROPERTY(EditAnywhere)
	float AngularVelocity;
};
