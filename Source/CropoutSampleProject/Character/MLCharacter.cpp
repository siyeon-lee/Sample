// Fill out your copyright notice in the Description page of Project Settings.


#include "MLCharacter.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/MLStatusComponent.h"
#include "NavigationSystem.h"
#include "MLBattleDefine.h"


// Sets default values
AMLCharacter::AMLCharacter()
{
 	// Set this Character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	if (SkeletalMeshClass != nullptr)
	{
		SkeletalMesh = NewObject<USkeletalMeshComponent>(this, SkeletalMeshClass, TEXT("SkeletalMesh"));
		SkeletalMesh->SetupAttachment(GetCapsuleComponent());
	}

	if (AttackCapsule == nullptr)
	{
		AttackCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCapsule"));
		AttackCapsule->SetCapsuleRadius(AttackRadius);
		AttackCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMLCharacter::OnBeginOverlap);
	}

	if (StatusComponent != nullptr)
	{
		StatusComponent = CreateDefaultSubobject<UMLStatusComponent>(TEXT("StatusComponent"));

	}
}

void AMLCharacter::InitCharacter(FGuid InUID, EMLTeamType InTeamType)
{
	GUID = InUID;
	if (StatusComponent != nullptr)
	{ 
		StatusComponent->InitStatus(InTeamType, DefaultStatusInfo);
	}
}

void AMLCharacter::BeAttacked(int32 InAttackValue)
{
	if (StatusComponent != nullptr)
	{
		StatusComponent->OnDead();
	}
	// 죽는 모션
	// 3초 뒤 Destroy;
	Destroy();
}

EMLTeamType AMLCharacter::GetTeamType() const
{
	if (StatusComponent == nullptr)
	{
		return EMLTeamType::None;
	}
	return StatusComponent->GetTeamType();
}

void AMLCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when sCharactered
void AMLCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMLCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 피아식별 필요

	if (IsValid(OtherActor) == true && OtherActor != GetOwner())
	{
		OtherActor->Destroy();
	}
}

bool AMLCharacter::MoveToLovcation(const FVector& InDestination)
{
	//UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	//if (NavSystem)
	{
		//FPathFindingQuery Query(this);
		//Query.SetGoalLocation(Destination);
		//Query.SetAllowPartialPaths(true); // 부분 경로 허용 여부 설정

		//FNavPathSharedPtr NavPath;
		//if (NavSystem->FindPathSync(Query, NavPath))
		//{
		//	GetController()->MoveAlongPath(NavPath, false); // 경로 따라 이동 명령
		//}
	}
	return false;
}

