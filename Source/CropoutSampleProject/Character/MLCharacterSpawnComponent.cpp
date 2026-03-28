// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MLCharacterSpawnComponent.h"
#include "MLCharacterSpawnComponent.h"
#include "MLCharacter.h"
#include "GameFrameWork/MLCharacterPoolManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMLCharacterSpawnComponent::UMLCharacterSpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMLCharacterSpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
// Called every frame
void UMLCharacterSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentTime += DeltaTime;
	if (CurrentTime > SpawnTimeInternal)
	{
		SpawnCharacter();
		CurrentTime = 0.f;
	}
	// ...
}

void UMLCharacterSpawnComponent::SpawnCharacter()
{
	if (SpawnCharacterList.Num() == 0)
	{
		//ML_LOG(Error, TEXT("SpawnCharacterList is Empty"));
		return;
	}

	const int32 CurrentSpawnCharacterNum = FMath::RandRange(1, SpawnCharacterMax);
	for (int i = 0; i < CurrentSpawnCharacterNum; ++i)
	{
		int32 SpawnCharacterIndex = FMath::RandRange(0, SpawnCharacterList.Num()-1);
		if (SpawnCharacterList[SpawnCharacterIndex] == nullptr)
		{
			continue;
		}
		if (UMLCharacterPoolManager* PoolManager = UMLCharacterPoolManager::GetCharacterPoolSystem(this))
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this->GetOwner();
			if (AMLCharacter* Owner = Cast< AMLCharacter>(GetOwner()))
			{
				PoolManager->SpawnCharacter<AMLCharacter>(Owner->GetTeamType(), SpawnCharacterList[SpawnCharacterIndex], GetSpawnTransform(), SpawnParameters);
			}
		}
	}
}

FTransform UMLCharacterSpawnComponent::GetSpawnTransform()
{
	//APlayerController* PlayerContorller = UGameplayStatics::GetPlayerController(this, 0);
	//if (PlayerContorller != nullptr)
	//{
	//	return FTransform();
	//}
	if (AActor* OwnerActor = GetOwner())
	{
		FVector BaseVector  = GetOwner()->GetActorLocation();
		FVector RandomUnitVector = FMath::VRand();
		float RandomDistance = FMath::FRandRange(SpawnMinRadius, SpawnMaxRadius);
		//플레이어 뒤로 스폰되지 않도록.
		FVector SpawnStartOffset = GetOwner()->GetActorForwardVector() * SpawnMaxRadius * 2;
		FVector  ResultVector = BaseVector + SpawnStartOffset + RandomDistance * RandomUnitVector;
		ResultVector.Z = BaseVector.Z;
		//FRotator ResultRotator = PlayerContorller->GetControlRotation();//GetOwner()->GetActorRotation();
		//ResultRotator.Roll = 0.f;
		//ResultRotator.Pitch = 0.f;
		//ResultRotator.Yaw -= 90.f;
		return FTransform(GetOwner()->GetActorRotation(), ResultVector);
	
	}
	return FTransform();
}

