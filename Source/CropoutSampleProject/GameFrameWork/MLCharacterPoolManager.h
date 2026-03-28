// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "MLBattleDefine.h"
#include "Kismet/GameplayStatics.h"

#include "MLCharacterPoolManager.generated.h"

class AMLCharacter;
enum class EMLTeamType : uint8;

UCLASS()
class CROPOUTSAMPLEPROJECT_API UMLCharacterPoolManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	friend class UMLEventSystem;
public:
	static UMLCharacterPoolManager* Get(const UWorld* WorldObject);
	static UMLCharacterPoolManager* GetCharacterPoolSystem(const UObject* WorldObject);

public:
	template< class T >
	bool SpawnCharacter(EMLTeamType InTeamType, UClass* Class, FTransform const& Transform,  FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		SpawnParameters.bDeferConstruction = true;

		if (AMLCharacter* ChildCharacter = GetWorld()->SpawnActor<T>(Class, Transform, SpawnParameters))
		{
			{
				FGuid NewID = MakeUniqueID();
				SpawnedCharacterList.Emplace(NewID, ChildCharacter);
				ChildCharacter->InitCharacter(NewID, InTeamType);
			}
			UGameplayStatics::FinishSpawningActor(ChildCharacter, Transform);
			return true;
		}
		return false;
	}

	template< class T >
	AMLCharacter* SpawnCharacter_ptr(EMLTeamType InTeamType, UClass* Class, FTransform const& Transform,  FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		SpawnParameters.bDeferConstruction = true;
		if (AMLCharacter* ChildCharacter = GetWorld()->SpawnActor<T>(Class, Transform, SpawnParameters))
		{
			{
				FGuid NewID = MakeUniqueID();
				SpawnedCharacterList.Emplace(NewID, ChildCharacter);
				ChildCharacter->InitCharacter(NewID, InTeamType);
			}
			UGameplayStatics::FinishSpawningActor(ChildCharacter, Transform);

			return ChildCharacter;
		}
		return nullptr;
	}

	template< class T >
	FGuid SpawnCharacter_Guid(EMLTeamType InTeamType, UClass* Class, FTransform const& Transform,  FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		SpawnParameters.bDeferConstruction = true;

		if (AMLCharacter* ChildCharacter = GetWorld()->SpawnActor<T>(Class, Transform, SpawnParameters))
		{
			{
				FGuid NewID = MakeUniqueID();
				SpawnedCharacterList.Emplace(NewID, ChildCharacter);
				ChildCharacter->InitCharacter(NewID, InTeamType);

			}
			UGameplayStatics::FinishSpawningActor(ChildCharacter, Transform);
			return NewID;
		}
		return FGuid(0);
	}
	void OnDestroyCharacter(FGuid InDestroyGUID);

private:
	AMLCharacter* GetCharacterByUID(FGuid InUID);
	
private:
	UMLCharacterPoolManager();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	FGuid MakeUniqueID();

	UPROPERTY()
	TMap<FGuid, AMLCharacter*> SpawnedCharacterList;
};

