// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_MovementComponent.h"


// Sets default values for this component's properties
UAS_MovementComponent::UAS_MovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAS_MovementComponent::BeginPlay()
{
	Super::BeginPlay();
	Position = GetOwner()->GetActorLocation();
}


// Called every frame
void UAS_MovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Position+=LinearVelocity * DeltaTime;
	Orientation +=AngularVelocity * DeltaTime;
	GetOwner()->SetActorLocation(Position);
	GetOwner()->SetActorRelativeRotation(FRotator(0,Orientation,0));

	LinearVelocity +=SteeringOutput.LinearVelocity;
	AngularVelocity +=SteeringOutput.AngularVelocity;

	// ...
}

