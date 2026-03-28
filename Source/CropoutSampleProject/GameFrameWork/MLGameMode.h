// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MLGameMode.generated.h"

enum class EMLTeamType : uint8;
class AMLCharacter;
/**
 * 
 */
UCLASS()
class CROPOUTSAMPLEPROJECT_API AMLGameMode : public AGameMode
{
	GENERATED_BODY()
public:

	AMLGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
private:
	void SpawnDefaultSummor(EMLTeamType InTeamType);
	const FName GetPlayerStartName(EMLTeamType InTeamType) const;
	TSubclassOf<AMLCharacter> GetDefaulClass(EMLTeamType InTeamType) const;
	UFUNCTION()
	void OnNotify_EndGame(EMLTeamType InLoseTeam);
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName PlayerStartName_Player = TEXT("Player");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName PlayerStartName_Enemy = TEXT("Enemy");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AMLCharacter> PlayerSummorClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AMLCharacter> EnemySummorClass;
};
