// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MLGameMode.generated.h"

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

};
