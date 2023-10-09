// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "MLBattleDefine.h"

#include "MLCharacterPoolManager.generated.h"

class AMLCharacter;
enum class EMLTeamType : uint8;

UCLASS()
class CROPOUTSAMPLEPROJECT_API UMLCharacterPoolManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UMLCharacterPoolManager* Get(const UWorld* WorldObject);
	static UMLCharacterPoolManager* GetCharacterPoolSystem(const UObject* WorldObject);

public:
	template< class T >
	bool SpawnCharacter(EMLTeamType InTeamType, UClass* Class, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		if (AMLCharacter* ChildCharacter = GetWorld()->SpawnActor<T>(Class, Transform, SpawnParameters))
		{
			FGuid NewID = MakeUniqueID();
			SpawnedCharacterList.Emplace(NewID, ChildCharacter);
			ChildCharacter->InitCharacter(NewID, InTeamType);
			return true;
		}
		return false;
	}
	void OnDestroyCharacter(FGuid InDestroyGUID);

	AMLCharacter* GetCharacterByUID(FGuid InUID);
	
private:
	UMLCharacterPoolManager();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	FGuid MakeUniqueID();

	UPROPERTY()
	TMap<FGuid, AMLCharacter*> SpawnedCharacterList;
};

