// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MLCharacterSpawnComponent.generated.h"


class AMLCharacter;

UENUM(BlueprintType)
enum class ESpawnType : uint8
{
	None,
	Plus,
	Multiply,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROPOUTSAMPLEPROJECT_API UMLCharacterSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMLCharacterSpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SpawnCharacter();

private:
	FTransform GetSpawnTransform();
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpawnTimeInternal = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpawnMinRadius = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpawnMaxRadius = 50.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AMLCharacter>> SpawnCharacterList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESpawnType SpawnerType = ESpawnType::Plus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 SpawnCharacterMax = 1;
private:
	float CurrentTime = 0.f;
};
