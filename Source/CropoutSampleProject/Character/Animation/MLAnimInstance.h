// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MLAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUTSAMPLEPROJECT_API UMLAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UMLAnimInstance(const FObjectInitializer& ObjectInitializer);

	virtual void NativeInitializeAnimation() override;
public:
	UPROPERTY(BlueprintReadOnly)
		class AMLCharacter* OwnerCharacter;
};
