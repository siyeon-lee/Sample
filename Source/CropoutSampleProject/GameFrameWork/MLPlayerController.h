// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MLPlayerController.generated.h"

struct FInputActionInstance;
class UInputMappingContext;
class UInputAction;
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

UCLASS()
class CROPOUTSAMPLEPROJECT_API AMLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	AMLPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;

	virtual bool DestroyNetworkActorHandled() override;
private:
#pragma region INPUT ACTIONS
	void MoveRight(const FInputActionInstance& Instance);
	void Zoom(const FInputActionInstance& Instance);
	void MoveForward(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	void StartToShot();
	void StopToShot();
#pragma endregion
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = Input)
	TArray<FActionInfo> ActionInfos;
};
