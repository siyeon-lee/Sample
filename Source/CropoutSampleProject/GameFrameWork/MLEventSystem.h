// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Subsystems/GameInstanceSubsystem.h"
#include "MLEventSystem.generated.h"

class UMLCharacterManagerPool;

UCLASS()
class CROPOUTSAMPLEPROJECT_API UMLEventSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UMLEventSystem* Get(const UWorld* WorldObject);
	static UMLEventSystem* GetEventSystem(const UObject* WorldObject);
	void OnAttack(FGuid InAttackerID, FGuid InDefenderID);
private:
	UMLEventSystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
private:
	TWeakPtr<UMLCharacterManagerPool> CharacterManagerPool;
};
