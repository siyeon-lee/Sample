// Fill out your copyright notice in the Description page of Project Settings.


#include "MLInputProcessComponent.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "CropoutSampleProject.h"




UMLInputProcessComponent::UMLInputProcessComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UMLInputProcessComponent::~UMLInputProcessComponent()
{
	UE_LOG(LogTemp, Warning, TEXT(""));
}

void UMLInputProcessComponent::SetUpInputSetting(UEnhancedInputComponent* InInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InInputComponent))
	{
		for (const FActionInfo& Info : ActionInfos)
		{
			switch (Info.InputType)
			{

			case EInputType::MoveRight:
			{
				EnhancedInputComponent->BindAction(Info.InputAction, ETriggerEvent::Triggered, this, &UMLInputProcessComponent::MoveRight);
			}
			break;

			case EInputType::Zoom:
			{
				EnhancedInputComponent->BindAction(Info.InputAction, ETriggerEvent::Triggered, this, &UMLInputProcessComponent::Zoom);
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
void UMLInputProcessComponent::OnPossessedPawn(APawn* Pawn)
{
	CurrentPawn = Pawn;
}
///////
// < Protected -----

// > private -----
#pragma region INPUT ACTIONS

void UMLInputProcessComponent::MoveForward(float Value)
{

	UE_LOG( LogTemp, Warning, TEXT("MoveForward"));
	if (CurrentPawn == nullptr)
	{
		return;
	}
	if (Value == 0.0f)
	{
		return;
	}

	// find out which way is forward
	//CurrentPawn->GetForwardVector();
//	const FRotator Rotation = GetControlRotation();
//	const FRotator YawRotation(0, Rotation.Yaw, 0);
//
	// get forward vector
	//APlayerController* PlayerController = GetPlayerController
	const FVector Direction = CurrentPawn->GetActorTransform().GetUnitAxis(EAxis::X);// FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	CurrentPawn->AddMovementInput(Direction, Value);
}

void UMLInputProcessComponent::MoveRight(const FInputActionInstance& Instance)
{
	if (CurrentPawn == nullptr)
	{
		return;
	}
	float Value = Instance.GetValue().Get<float>();
	if (Value == 0.0f)
	{
		return;
	}


	// find out which way is right
	if (AController* PC = CurrentPawn->GetController())
	{
		const FRotator Rotation = PC->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);;
		// get right vector 
		//const FVector Direction = CurrentPawn->GetActorTransform().GetUnitAxis(EAxis::X);// FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
		const float MoveSpeeed = 100;
		// add movement in that direction
		CurrentPawn->SetActorLocation(CurrentPawn->GetActorLocation() + Direction * Value * MoveSpeeed);
		//CurrentPawn->AddMovementInput(Direction, Value);
	}
}


void UMLInputProcessComponent::Zoom(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	if (Value == 0.0f)
	{
		return;
	}
	//카메라 지금 폰BP에 있음. 카메라시스템 연결 뒤 만들기
	//CameraSystem->Zoom(Value);
	// or
	// GameEventSystem->SendEvent_Zoom(Value);
}
#pragma endregion
// < private -----
