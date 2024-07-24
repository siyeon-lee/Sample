// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MLBattleDefine.h"
#include "MLCharacter.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UMLStatusComponent;
enum class EMLTeamType : uint8;

UENUM(BlueprintType)
enum class EMLCharacterState : uint8
{
	None,
	Idle,
	Walk,
	Attack,
	Damaged,
};

UCLASS()
class CROPOUTSAMPLEPROJECT_API AMLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this Character's properties
	AMLCharacter();
	virtual void InitCharacter(FGuid InUID, EMLTeamType InTeamType);
	virtual void BeAttacked(int32 InAttackValue);
public:
	EMLTeamType GetTeamType() const;
	FGuid GetUID() const { return GUID; }
protected:
	// Called when the game starts or when sCharactered
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool MoveToLovcation(const FVector& InDestination);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	EMLCharacterState GetCharacterState() const { return CharacterState; };
protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	TSubclassOf<USkeletalMeshComponent> SkeletalMeshClass;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	float AttackRadius = 20.f;

protected:
#pragma region THIRDPERSON_ENGINE_BASE
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
#pragma endregion //THIRDPERSON_ENGINE_BASE
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> AttackCapsule;

	UPROPERTY(Category = Status, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMLStatusComponent> StatusComponent;

	UPROPERTY(Category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FStatInfo DefaultStatusInfo;

	FGuid GUID;

	UPROPERTY(Category = State, VisibleAnywhere, BlueprintReadWrite)
	EMLCharacterState CharacterState = EMLCharacterState::Idle;
};
