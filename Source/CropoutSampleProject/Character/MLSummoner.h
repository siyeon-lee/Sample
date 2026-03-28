// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MLCharacter.h"
#include "MLSummoner.generated.h"

enum class EMLTeamType : uint8;
/**
 * 
 */
UCLASS()
class CROPOUTSAMPLEPROJECT_API AMLSummoner : public AMLCharacter
{
	GENERATED_BODY()
public:
	AMLSummoner();

public:
	virtual void OnDead() override;

protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMLCharacterSpawnComponent* SpawnerComponent;


	enum class EMLTeamType TeamType = EMLTeamType::Player;
};
