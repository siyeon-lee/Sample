// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MLInputProcessComponent.generated.h"

struct FInputActionInstance;
class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;
class APawn;
/**
 * 
 */

UENUM(BlueprintType)
enum class EInputType :uint8
{
	None,
	MoveRight,
	Zoom,
	Max
};

USTRUCT(BlueprintType)
struct FActionInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputAction* InputAction;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EInputType InputType;
};

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class CROPOUTSAMPLEPROJECT_API UMLInputProcessComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UMLInputProcessComponent(const FObjectInitializer& ObjectInitializer);
	virtual ~UMLInputProcessComponent();
	void SetUpInputSetting(UEnhancedInputComponent* InInputComponent);
	void OnPossessedPawn(APawn* Pawn);
private:
	void MoveRight(const FInputActionInstance& Instance);
	void Zoom(const FInputActionInstance& Instance);
	void MoveForward(float Value);
private: 
	UPROPERTY(Transient )
	APawn* CurrentPawn;
public:
	UPROPERTY(Transient)
		UInputMappingContext* InputMapping;

	UPROPERTY(Transient)
		TArray<FActionInfo> ActionInfos;
};
