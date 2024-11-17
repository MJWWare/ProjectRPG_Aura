// Copyright MJWWare


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{

	const int32 WidgetSwitcherIndex = SlotStatus.GetValue();
	//todo: check slot status based on loaded data .
	SetWidgetSwitcherIndex.Broadcast(WidgetSwitcherIndex);
	
}

void UMVVM_LoadSlot::SetPlayerName(FString InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}

void UMVVM_LoadSlot::SetLoadSlotName(FString InLoadSlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, InLoadSlotName);
}
