// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MLPlayerController.generated.h"

struct FInputActionInstance;
class UMLInputProcessComponent;
class UInputMappingContext;
struct FActionInfo;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CROPOUTSAMPLEPROJECT_API AMLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	AMLPlayerController(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMLInputProcessComponent* InputProcessComp;


	UPROPERTY(EditAnywhere, Category = Input)
		UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = Input)
		TArray<FActionInfo> ActionInfos;
};
