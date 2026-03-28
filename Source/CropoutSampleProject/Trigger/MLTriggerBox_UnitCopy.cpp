// Fill out your copyright notice in the Description page of Project Settings.


#include "MLTriggerBox_UnitCopy.h"
#include "Character/MLCharacter.h"
#include "Character/MLCharacterSpawnComponent.h"
#include "GameFrameWork/MLCharacterPoolManager.h"
#include "Kismet/GameplayStatics.h"



AMLTriggerBox_UnitCopy::AMLTriggerBox_UnitCopy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void AMLTriggerBox_UnitCopy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (AMLCharacter* TargetCharacter =  Cast<AMLCharacter>(OtherActor))
	{
		if (UMLCharacterPoolManager* PoolManager = UMLCharacterPoolManager::GetCharacterPoolSystem(this))
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = TargetCharacter->GetOwner();
			PoolManager->SpawnCharacter<AMLCharacter>(TargetCharacter->GetTeamType(), TargetCharacter->GetClass(), TargetCharacter->GetActorTransform(), SpawnParameters);

		}
		return;
	}

}

void AMLTriggerBox_UnitCopy::NotifyActorEndOverlap(AActor* OtherActor)
{

}
