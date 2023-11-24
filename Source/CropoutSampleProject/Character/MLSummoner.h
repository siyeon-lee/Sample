// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MLCharacter.h"
#include "MLSummoner.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUTSAMPLEPROJECT_API AMLSummoner : public AMLCharacter
{
	GENERATED_BODY()
public:
	AMLSummoner();

protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMLCharacterSpawnComponent* SpawnerComponent;
};
