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
	IsDead = true;
	StatusInfo.HP -= InDamage;
}

const FStatInfo& UMLStatusComponent::GetStatInfo() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return StatusInfo;
}
