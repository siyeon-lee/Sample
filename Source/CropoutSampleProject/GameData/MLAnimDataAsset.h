// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MLAnimDataAsset.generated.h"

/**
 * 
 */
enum class EMLCharacterState : uint8;
class UAnimMontage;

UCLASS()
class CROPOUTSAMPLEPROJECT_API UMLAnimDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EMLCharacterState, UAnimMontage*> MontageList;


};
