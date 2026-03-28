// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger/MLTriggerBox.h"
#include "MLTriggerBox_UnitCopy.generated.h"

enum class EMLTeamType : uint8;
UENUM(BlueprintType)
enum class EOperatorType : uint8
{
	None,
	Plus,
	Multiply,
	//이것 두 개는 객체단위가 아니라 무리 단위로 충돌 체크해야 가능함.
	//Minus,
	//divide,
};
/**
 * 
 */
UCLASS()
class CROPOUTSAMPLEPROJECT_API AMLTriggerBox_UnitCopy : public AMLTriggerBox
{
	GENERATED_BODY()
public:
	AMLTriggerBox_UnitCopy(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EMLTeamType TargetType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EOperatorType OperatorType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ComputeNum = 1;
};
