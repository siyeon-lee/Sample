// Fill out your copyright notice in the Description page of Project Settings.


#include "MLGameMode.h"
#include "MLGameState.h"
#include "MLPlayerController.h"
#include "MLPlayerState.h"
#include "Character/MLCharacter.h"
#include "MLHud.h"

AMLGameMode::AMLGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AMLGameState::StaticClass();
	PlayerControllerClass = AMLPlayerController::StaticClass();
	PlayerStateClass = AMLPlayerState::StaticClass();
	DefaultPawnClass = AMLCharacter::StaticClass();
	HUDClass = AMLHUD::StaticClass();
}

void AMLGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->SpawnActor<AMLCharacter>(DefaultPawnClass, FTransform());
	//PlayerCont
}
