// Fill out your copyright notice in the Description page of Project Settings.


#include "MLPlayerController.h"
#include <CropoutSampleProject/CropoutSampleProject.h>


// > Protected ------
void AMLPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ML_LOG(Log, TEXT("Game Start"));
}

void AMLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

		// Set up gameplay key bindings
	InputComponent->BindAction("Shot", IE_Pressed, this, &AMLPlayerController::StartToShot);
	InputComponent->BindAction("Shot", IE_Released, this, &AMLPlayerController::StopToShot);

	InputComponent->BindAxis("MoveForward", this, &AMLPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMLPlayerController::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &AMLPlayerController::AddYawInput);
	InputComponent->BindAxis("TurnRate", this, &AMLPlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &AMLPlayerController::AddYawInput);
	InputComponent->BindAxis("LookUpRate", this, &AMLPlayerController::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AMLPlayerController::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AMLPlayerController::TouchStopped);

}
bool AMLPlayerController::DestroyNetworkActorHandled()
{
	//데디케이트 상황에서 다른 클라이언트가 넷컬링 된 상태에서 게임을 종료했을 시, 플로터 해제를 위해 넣은 코드
	//AMLGameCharacter* CurrentPawn = GetPawn<AMLGameCharacter>();
	//if (CurrentPawn != nullptr && CurrentPawn->IsValidLowLevel() == true)
	//{
	//	CurrentPawn->ReleaseCharacter();
	//}
	return Super::DestroyNetworkActorHandled();
}
// < Protected -----

// > private -----
#pragma region INPUT ACTIONS

void AMLPlayerController::MoveForward(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}

	APawn* CurrentPawn = GetPawn();
	if (CurrentPawn == nullptr || CurrentPawn->IsValidLowLevel() == false)
	{
		return;
	}

	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	CurrentPawn->AddMovementInput(Direction, Value);
}

void AMLPlayerController::MoveRight(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}

	APawn* CurrentPawn = GetPawn();
	if (CurrentPawn == nullptr || CurrentPawn->IsValidLowLevel() == false)
	{
		return;
	}
	// find out which way is right
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	CurrentPawn->AddMovementInput(Direction, Value);
}

void AMLPlayerController::TurnAtRate(float Rate)
{
	if (Rate == 0)
	{
		return;
	}
	AddYawInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMLPlayerController::LookUpAtRate(float Rate)
{
	if (Rate == 0)
	{
		return;
	}
	AddPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMLPlayerController::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{

}

void AMLPlayerController::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{

}

void AMLPlayerController::StartToShot()
{

}

void AMLPlayerController::StopToShot()
{

}
#pragma endregion
// < private -----
