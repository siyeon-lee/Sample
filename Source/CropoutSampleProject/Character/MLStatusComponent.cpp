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

void UMLStatusComponent::OnDead()
{
	IsDead = true;
	StatusInfo.HP = 0;
}
