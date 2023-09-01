// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MLCharacter.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CROPOUTSAMPLEPROJECT_API AMLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this Character's properties
	AMLCharacter();

protected:
	// Called when the game starts or when sCharactered
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
#pragma region THIRDPERSON_ENGINE_BASE
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	USpringArmComponent* CameraBoom;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* SkeletalMesh;
#pragma endregion //THIRDPERSON_ENGINE_BASE

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	TSubclassOf<USkeletalMeshComponent> SkeletalMeshClass;
};
