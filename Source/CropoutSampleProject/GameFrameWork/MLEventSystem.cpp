// Fill out your copyright notice in the Description page of Project Settings.
#include "MLEventSystem.h"
#include "GameFrameWork/MLCharacterPoolManager.h"
#include "Character/MLCharacter.h"
#include "Character/MLSummoner.h"

UMLEventSystem::UMLEventSystem()
{
	OnAttackEvent.AddDynamic(this, &UMLEventSystem::OnAttack);
	OnDeadEvent.AddDynamic(this, &UMLEventSystem::OnDead);
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
	UE_LOG(LogTemp, Error, TEXT("OnAttack."));
	if (UMLCharacterPoolManager* CharacterPool = GetGameInstance()->GetSubsystem<UMLCharacterPoolManager>())
	{
		if (InAttackerID.IsValid() == false || InDefenderID.IsValid() == false)
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
		//이건노티파이로 바꿔야지
		Attacker->SetCharacterState(EMLCharacterState::Attack);
		Defender->SetCharacterState(EMLCharacterState::Damaged);
		Defender->BeAttacked(999);
	}
}

void UMLEventSystem::OnDead(FGuid InDeadID)
{
	UE_LOG(LogTemp, Error, TEXT("OnDead."));
	if (UMLCharacterPoolManager* CharacterPool = GetGameInstance()->GetSubsystem<UMLCharacterPoolManager>())
	{
		if (InDeadID.IsValid() == false)
		{
			return;
		}

		TWeakObjectPtr<AMLCharacter> DeadCharacter = CharacterPool->GetCharacterByUID(InDeadID);
		if (DeadCharacter.IsValid())
		{
			DeadCharacter->OnDead();
		}

		if (DeadCharacter->IsA(AMLSummoner::StaticClass()))
		{
		}
	}
}
