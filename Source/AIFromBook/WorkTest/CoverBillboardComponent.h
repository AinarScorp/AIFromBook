// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"
#include "CoverBillboardComponent.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable, HideCategories = (HLOD,PathTracing,Navigation,Tags, Cooking, LOD,TextureStreaming,Mobile, RayTracing,AssetUserData))
class AIFROMBOOK_API UCoverBillboardComponent : public UBillboardComponent
{
	GENERATED_BODY()

public:
	UCoverBillboardComponent();
	UFUNCTION(BlueprintCallable, DisplayName = "Can Occupy")
	bool CanOccupyCover();
	UFUNCTION(BlueprintCallable, DisplayName = "Try Occupy")
	bool TryOccupyCover(AActor* AttemptingToOccupyActor);
	UFUNCTION(BlueprintCallable, DisplayName = "Stop Occupying")
	void StopOccupyingCover(AActor* CurrentlyOccupyingActor);
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void DrawGizmos();
protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION(CallInEditor,BlueprintCallable)
	void RemoveCover();
	void CalculateCoverDirection();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector CoverDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector Location;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsOccupied;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> OccupyingActor;

};
