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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 HP = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 AttackPower = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 DefensePower = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Speed = 0;
};
 