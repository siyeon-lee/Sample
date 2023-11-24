// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Subsystems/GameInstanceSubsystem.h"
#include "MLEventSystem.generated.h"

class UMLCharacterManagerPool;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttackEvent, FGuid, AttackerID, FGuid, DefenderID);

UCLASS()
class CROPOUTSAMPLEPROJECT_API UMLEventSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UMLEventSystem();
	FAttackEvent OnAttackEvent;
public:
	static UMLEventSystem* Get(const UWorld* WorldObject);
	static UMLEventSystem* GetEventSystem(const UObject* WorldObject);
private:
	UFUNCTION()
	void OnAttack(FGuid InAttackerID, FGuid InDefenderID);
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
private:
	TWeakPtr<UMLCharacterManagerPool> CharacterManagerPool;
};
