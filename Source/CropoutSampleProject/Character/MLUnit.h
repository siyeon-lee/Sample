// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MLCharacter.h"
#include "MLUnit.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUTSAMPLEPROJECT_API AMLUnit : public AMLCharacter
{
	GENERATED_BODY()
public:
	virtual void InitCharacter(FGuid InUID, EMLTeamType InTeamType) override;
	virtual void Tick(float InDeltaTime) override;
};
