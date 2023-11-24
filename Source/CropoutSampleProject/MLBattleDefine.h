// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "MLBattleDefine.generated.h"
UENUM(BlueprintType)
enum class EMLTeamType : uint8
{
	None,
	Player,
	Enemy,
};

USTRUCT(BlueprintType)
struct FStatInfo
{
	GENERATED_BODY()
	int32 HP = 0;
	int32 Attack = 0;
	int32 Defend = 0;
};
 