// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MLBattleDefine.h"
#include "MLStatusComponent.generated.h"

enum class EMLTeamType : uint8;
struct FStatInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROPOUTSAMPLEPROJECT_API UMLStatusComponent : public UActorComponent
{
	GENERATED_BODY()
	friend class AMLCharacter;
public:	
	// Sets default values for this component's properties
	UMLStatusComponent();
public:
	void InitStatus(EMLTeamType InTeamType, FStatInfo InInfo);
	virtual void OnDead();

	EMLTeamType GetTeamType() const { return TeamType; }
private:
	EMLTeamType TeamType;
	bool IsDead = false;
	FStatInfo StatusInfo;
};
