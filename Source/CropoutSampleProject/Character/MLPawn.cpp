// Fill out your copyright notice in the Description page of Project Settings.


#include "MLPawn.h"

// Sets default values
AMLPawn::AMLPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMLPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMLPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMLPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

