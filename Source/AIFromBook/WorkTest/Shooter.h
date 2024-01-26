// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shooter.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIsBehindCoverChangedSignature, bool, NewValue);

UCLASS()
class AIFROMBOOK_API AShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter();
	UFUNCTION(BlueprintCallable)
	void StopOccupyingCover();
	UFUNCTION(BlueprintCallable)
	void SetIsBehindCover(bool NewIsBehindCover);
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "CrouchLevel")
	float GetCrouchLevel() const {return CrouchLevel;}
private:
	UFUNCTION()
	void ChangeCrouchLevel();
public:
	UPROPERTY(BlueprintAssignable)
	FOnIsBehindCoverChangedSignature OnIsBehindCoverChanged;
private:
	UPROPERTY(VisibleAnywhere, meta = (ClampMin = 0, ClampMax = 1))
	float CrouchLevel;
	UPROPERTY(VisibleAnywhere)
	bool IsBehindCover;
	
	FTimerHandle CrouchLevelModificationTimer;
};
