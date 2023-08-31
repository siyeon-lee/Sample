// Fill out your copyright notice in the Description page of Project Settings.


#include "MLPlayerController.h"
#include "CropoutSampleProject.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "InputAction.h"
#include "InputMappingContext.h"


// > Protected ------

AMLPlayerController::AMLPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OverridePlayerInputClass = UEnhancedInputComponent::StaticClass();
}

void AMLPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (const ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

void AMLPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AMLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		for (const FActionInfo& Info : ActionInfos)
		{
			switch (Info.InputType)
			{

			case EInputType::MoveRight:
			{
				EnhancedInputComponent->BindAction(Info.InputAction, ETriggerEvent::Triggered, this, &AMLPlayerController::MoveRight);
			}
			break;
			
			case EInputType::Zoom:
			{
				EnhancedInputComponent->BindAction(Info.InputAction, ETriggerEvent::Triggered, this, &AMLPlayerController::Zoom);
			}
			break;
			case EInputType::Max:
				break;
			default:
				break;
			}
		}
	}
}


bool AMLPlayerController::DestroyNetworkActorHandled()
{

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

void AMLPlayerController::MoveRight(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
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


void AMLPlayerController::Zoom(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	if (Value == 0.0f)
	{
		return;
	}

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
