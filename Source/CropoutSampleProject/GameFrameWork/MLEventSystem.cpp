// Fill out your copyright notice in the Description page of Project Settings.
#include "MLEventSystem.h"
#include "GameFrameWork/MLCharacterPoolManager.h"
#include "Character/MLCharacter.h"
#include "Character/MLSummoner.h"
#include "GameFramework/PlayerController.h"

UMLEventSystem::UMLEventSystem()
{
	AttackEvent.AddDynamic(this, &UMLEventSystem::OnAttack);
	DeadEvent.AddDynamic(this, &UMLEventSystem::OnDead);
	SummonerDeadEvent.AddDynamic(this, &UMLEventSystem::OnEndGame);
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

		if (Attacker->IsDead() || Defender->IsDead())
		{
			return;
		}

		bool bIsFriend = Attacker->GetTeamType() == Defender->GetTeamType();
		if (bIsFriend == true)
		{
			return;
		}

		//이건노티파이로 바꿔야지
		const int32 DamageMount = FMath::Max(0, Attacker->GetStatInfo().AttackPower - Defender->GetStatInfo().DefensePower);
	
		Attacker->DoAttack();
		Defender->BeAttacked(DamageMount);	//Attacker->대미지양으로 
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

	}
}

void UMLEventSystem::OnEndGame(EMLTeamType InDeadSummerTeam)
{
	// ShowUI

	// EndPlayGame
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, false);
	}
}
