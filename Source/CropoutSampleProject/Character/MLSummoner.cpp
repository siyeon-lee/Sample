// Fill out your copyright notice in the Description page of Project Settings.


#include "MLSummoner.h"
#include "Character/MLCharacterSpawnComponent.h"
AMLSummoner::AMLSummoner()
{
	if (SpawnerComponent == nullptr)
	{
		SpawnerComponent = CreateDefaultSubobject<UMLCharacterSpawnComponent>(TEXT("SpawnerComponent"));
	}

}
