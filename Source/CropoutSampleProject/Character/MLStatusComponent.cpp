#include "MLStatusComponent.h"
#include "MLBattleDefine.h"

UMLStatusComponent::UMLStatusComponent()
{
}

void UMLStatusComponent::InitStatus(EMLTeamType InTeamType, FStatInfo InInfo)
{
	TeamType = InTeamType;
	StatusInfo = InInfo;
}

void UMLStatusComponent::OnAttacked(int32 InDamage)
{
	if (InDamage < 0)
	{
		return;
	}
	IsDead = true;
	StatusInfo.HP -= InDamage;
	StatusInfo.HP = FMath::Max(0, StatusInfo.HP);
}

const FStatInfo& UMLStatusComponent::GetStatInfo() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return StatusInfo;
}
