// Fill out your copyright notice in the Description page of Project Settings.


#include "MLGameMode.h"
#include "MLGameState.h"
#include "MLPlayerController.h"
#include "MLPlayerState.h"
#include "Character/MLCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "MLHud.h"
#include "EngineUtils.h"
#include "GameFrameWork/MLCharacterPoolManager.h"

AMLGameMode::AMLGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AMLGameState::StaticClass();
	PlayerControllerClass = AMLPlayerController::StaticClass();
	PlayerStateClass = AMLPlayerState::StaticClass();
	DefaultPawnClass = nullptr;// AMLCharacter::StaticClass();
	HUDClass = AMLHUD::StaticClass();
}

void AMLGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDefaultSummor(EMLTeamType::Player);
	SpawnDefaultSummor(EMLTeamType::Enemy);
}

//이거 따로 상속으로 빼던가 컨포넌트로 빼던가 너무 더럽
void AMLGameMode::SpawnDefaultSummor(EMLTeamType InTeamType)
{
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* Start = *It;
		if (Start && Start->PlayerStartTag == GetPlayerStartName(InTeamType))
		{
			if (UMLCharacterPoolManager* PoolManager = UMLCharacterPoolManager::GetCharacterPoolSystem(this))
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = this;
				// 이 부분을 좀 깔쌈하게...
				AMLCharacter* SpawnCharacter = PoolManager->SpawnCharacter_ptr<AMLCharacter>(InTeamType, GetDefaulClass(InTeamType), Start->GetActorTransform(), SpawnParameters);
				if (InTeamType == EMLTeamType::Player)
				{
					if(APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController())
					{
						PC->Possess(SpawnCharacter);
					}

				}
			}
			return;
		}
	}
}

TSubclassOf<AMLCharacter> AMLGameMode::GetDefaulClass(EMLTeamType InTeamType) const
{
	switch (InTeamType)
	{
	case EMLTeamType::Player:
		return PlayerSummorClass;
	case EMLTeamType::Enemy:
		return EnemySummorClass;
	}
	return nullptr;

}

void AMLGameMode::OnNotify_EndGame(EMLTeamType InWinTeam)
{
	UE_LOG(LogTemp, Error, TEXT("EndGame."));
}

const FName AMLGameMode::GetPlayerStartName(EMLTeamType InTeamType) const
{
	switch (InTeamType)
	{
	case EMLTeamType::Player:
		return PlayerStartName_Player;
	case EMLTeamType::Enemy:
		return PlayerStartName_Enemy;
	}
	return NAME_None;
}
