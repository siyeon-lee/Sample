// Fill out your copyright notice in the Description page of Project Settings.
#include "MLCharacterPoolManager.h"
#include "Character/MLCharacter.h"
#include "Kismet/KismetGuidLibrary.h"

UMLCharacterPoolManager* UMLCharacterPoolManager::Get(const UWorld* WorldObject)
{
	if (WorldObject)
	{
		return UGameInstance::GetSubsystem<UMLCharacterPoolManager>(WorldObject->GetGameInstance());
	}

	return nullptr;
}

UMLCharacterPoolManager* UMLCharacterPoolManager::GetCharacterPoolSystem(const UObject* WorldObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		return UMLCharacterPoolManager::Get(World);
	}

	return nullptr;
}

void UMLCharacterPoolManager::OnDestroyCharacter(FGuid InDestroyGUID)
{
	if (SpawnedCharacterList.Contains(InDestroyGUID) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Guid Is Invalid."));
		return;
	}
	SpawnedCharacterList[InDestroyGUID] = nullptr;
	SpawnedCharacterList.Remove(InDestroyGUID);
}

AMLCharacter* UMLCharacterPoolManager::GetCharacterByUID(FGuid InUID)
{
	return *SpawnedCharacterList.Find(InUID);
	//return nullptr;
}

UMLCharacterPoolManager::UMLCharacterPoolManager()
{
}

void UMLCharacterPoolManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMLCharacterPoolManager::Deinitialize()
{
	Super::Deinitialize();
	for (auto& SpawnEntry : SpawnedCharacterList)
	{
		if (SpawnEntry.Value != nullptr)
		{
			SpawnEntry.Value->Destroy();
			SpawnEntry.Value = nullptr;
		}
	}
	SpawnedCharacterList.Empty();
}

FGuid UMLCharacterPoolManager::MakeUniqueID()
{
	// 디스폰 된 얘를 재활용 할 수 있는......
	return UKismetGuidLibrary::NewGuid();
}
