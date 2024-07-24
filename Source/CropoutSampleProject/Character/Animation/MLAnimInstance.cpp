// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/MLAnimInstance.h"
#include "Character/MLCharacter.h"
#include "MLAnimInstance.h"

UMLAnimInstance::UMLAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMLAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<AMLCharacter>(GetOwningActor());

}
