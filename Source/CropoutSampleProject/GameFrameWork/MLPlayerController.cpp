// Fill out your copyright notice in the Description page of Project Settings.


#include "MLPlayerController.h"
#include "CropoutSampleProject.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "MLInputProcessComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"


// > Protected ------

AMLPlayerController::AMLPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	//InputProcessComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	InputProcessComp = CreateDefaultSubobject<UMLInputProcessComponent>(TEXT("InputProcessComp"));


	AddOwnedComponent(InputProcessComp);
	OverridePlayerInputClass = UEnhancedInputComponent::StaticClass();
}

void AMLPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (const ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputProcessComp != nullptr)
			{
				Subsystem->AddMappingContext(InputMapping, 0);
			}
		}
	}

}

void AMLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputProcessComp != nullptr)
	{
		InputProcessComp->ActionInfos = this->ActionInfos;
		InputProcessComp->SetUpInputSetting(Cast<UEnhancedInputComponent>(InputComponent));
	}
}

void AMLPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (InputProcessComp != nullptr)
	{
		InputProcessComp->OnPossessedPawn(aPawn);;
	}
}
// < Protected -----
