// Fill out your copyright notice in the Description page of Project Settings.
#include "MLEventSystem.h"
#include "GameFrameWork/MLCharacterPoolManager.h"
#include "Character/MLCharacter.h"
UMLEventSystem::UMLEventSystem()
{
}

UMLEventSystem* UMLEventSystem::Get(const UWorld* World)
{
	if (World)
	{
		return UGameInstance::GetSubsystem<UMLEventSystem>(World->GetGameInstance());
	}

	return nullptr;
}

UMLEventSystem* UMLEventSystem::GetEventSystem(const UObject* WorldObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		return UMLEventSystem::Get(World);
	}

	return nullptr;
}

void UMLEventSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMLEventSystem::Deinitialize()
{
	Super::Deinitialize();
}

void UMLEventSystem::OnAttack(FGuid InAttackerID, FGuid InDefenderID)
{
	UMLCharacterPoolManager* CharacterPool = this->GetGameInstance()->GetSubsystem<UMLCharacterPoolManager>();
	if (CharacterPool == nullptr)
	{
		return;
	}

	TWeakObjectPtr<AMLCharacter> Attacker = CharacterPool->GetCharacterByUID(InAttackerID);
	TWeakObjectPtr<AMLCharacter> Defender = CharacterPool->GetCharacterByUID(InDefenderID);
	if (Attacker.IsValid() == false || Defender.IsValid() == false)
	{
		return;
	}

	bool IsFriend = Attacker->GetTeamType() == Defender->GetTeamType();
	if (IsFriend == true)
	{
		return;
	}

	Defender->BeAttacked(999);
}
