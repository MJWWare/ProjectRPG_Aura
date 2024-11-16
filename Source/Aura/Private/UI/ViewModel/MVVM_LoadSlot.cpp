// Copyright MJWWare


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{

	//const int32 WidgetSwitcherIndex = SlotStatus.GetValue();
	//todo: check slot status based on loaded data .
	SetWidgetSwitcherIndex.Broadcast(2);
	
}

void UMVVM_LoadSlot::SetLoadSlotName(FString InLoadSlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, InLoadSlotName);
}
