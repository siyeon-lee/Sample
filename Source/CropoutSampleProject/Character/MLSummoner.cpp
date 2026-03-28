// Fill out your copyright notice in the Description page of Project Settings.


#include "MLSummoner.h"
#include "Character/MLCharacterSpawnComponent.h"
#include "GameFrameWork/MLEventSystem.h"

AMLSummoner::AMLSummoner()
{
	if (SpawnerComponent == nullptr)
	{
		SpawnerComponent = CreateDefaultSubobject<UMLCharacterSpawnComponent>(TEXT("SpawnerComponent"));
	}

}

void AMLSummoner::OnDead()
{
	Super::OnDead();

	UMLEventSystem::Get(GetWorld())->SummonerDeadEvent.Broadcast(GetTeamType());
}
