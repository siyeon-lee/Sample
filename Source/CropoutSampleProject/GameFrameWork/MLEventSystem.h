// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Subsystems/GameInstanceSubsystem.h"
#include "MLEventSystem.generated.h"

class UMLCharacterManagerPool;

enum class EMLTeamType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttackEvent, FGuid, AttackerID, FGuid, DefenderID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeadEvent, FGuid, DeadUID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVictoryEvent, EMLTeamType, VictoryTeamType);


UCLASS()
class CROPOUTSAMPLEPROJECT_API UMLEventSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UMLEventSystem();
	FAttackEvent AttackEvent;
	FDeadEvent DeadEvent;
	FVictoryEvent SummonerDeadEvent;
public:
	static UMLEventSystem* Get(const UWorld* WorldObject);
	static UMLEventSystem* GetEventSystem(const UObject* WorldObject);
private:
	UFUNCTION()
	void OnAttack(FGuid InAttackerID, FGuid InDefenderID);
	
	UFUNCTION()
	void OnDead(FGuid InDeadID);

	UFUNCTION()
	void OnEndGame(EMLTeamType InVictoryTeam);
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
private:
	TWeakPtr<UMLCharacterManagerPool> CharacterManagerPool;
};
