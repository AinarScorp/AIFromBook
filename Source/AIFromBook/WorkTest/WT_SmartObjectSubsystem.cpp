// Fill out your copyright notice in the Description page of Project Settings.


#include "WT_SmartObjectSubsystem.h"

TArray<UCoverBillboardComponent*> UWT_SmartObjectSubsystem::GetCoverComponents()
{
	TArray<UCoverBillboardComponent*> OutArray;
	CoverComponents.GenerateValueArray(OutArray);
	return OutArray;
}

UCoverBillboardComponent* UWT_SmartObjectSubsystem::GetCoverComponent(FVector Location)
{
	return CoverComponents[Location];
}
