// Fill out your copyright notice in the Description page of Project Settings.


#include "MLUnit.h"

void AMLUnit::InitCharacter(FGuid InUID, EMLTeamType InTeamType)
{
	Super::InitCharacter(InUID, InTeamType);
	CharacterState = EMLCharacterState::Walk;
}

void AMLUnit::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);
}
