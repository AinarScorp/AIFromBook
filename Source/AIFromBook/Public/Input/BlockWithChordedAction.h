// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "BlockWithChordedAction.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Blocker Chorded Action", NotInputConfigurable = "true"))
class AIFROMBOOK_API UBlockWithChordedAction : public UInputTriggerChordAction
{
	GENERATED_BODY()
protected:
	virtual ETriggerType GetTriggerType_Implementation() const override { return ETriggerType::Blocker; }
};
