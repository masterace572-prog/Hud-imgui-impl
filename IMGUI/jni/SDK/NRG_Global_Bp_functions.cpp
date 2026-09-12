// PUBG MOBILE (2.8.1) SDKGen by @TEAMNRG1 | @TeamNRG_MOD | (NRG Owner: @TMNrgOwnerBot)
#include "../SDK.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Global_Bp.Global_Bp_C.InitFireGyroSensibilitySettingData
// (NetResponse, NetMulticast, Protected, Delegate, HasOutParms, NetClient, DLLImport, BlueprintEvent, BlueprintPure, Const)
// Parameters:
// class USettingConfig_C*        ServerSettingConfig            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::InitFireGyroSensibilitySettingData(class USettingConfig_C* ServerSettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.InitFireGyroSensibilitySettingData");

	UGlobal_Bp_C_InitFireGyroSensibilitySettingData_Params params;
	params.ServerSettingConfig = ServerSettingConfig;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.MapFromCBToESBH
// (Event, NetResponse, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        SettingConfig                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::MapFromCBToESBH(class USettingConfig_C* SettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.MapFromCBToESBH");

	UGlobal_Bp_C_MapFromCBToESBH_Params params;
	params.SettingConfig = SettingConfig;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.InitMirrorObjMapPickupSetting
// (NetReliable, NetRequest, Exec, Native, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        ServerSettingConfig            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::STATIC_InitMirrorObjMapPickupSetting(class USettingConfig_C* ServerSettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.InitMirrorObjMapPickupSetting");

	UGlobal_Bp_C_InitMirrorObjMapPickupSetting_Params params;
	params.ServerSettingConfig = ServerSettingConfig;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.InitThrowObjMapPickupSetting
// (NetRequest, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        ServerSettingConfig            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::STATIC_InitThrowObjMapPickupSetting(class USettingConfig_C* ServerSettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.InitThrowObjMapPickupSetting");

	UGlobal_Bp_C_InitThrowObjMapPickupSetting_Params params;
	params.ServerSettingConfig = ServerSettingConfig;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.InitDrugMapPickupSetting
// (Native, Event, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        ServerSettingConfig            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::STATIC_InitDrugMapPickupSetting(class USettingConfig_C* ServerSettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.InitDrugMapPickupSetting");

	UGlobal_Bp_C_InitDrugMapPickupSetting_Params params;
	params.ServerSettingConfig = ServerSettingConfig;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.InitBasicSettingData
// (NetRequest, Exec, Event, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        ServerSettingConfig            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::STATIC_InitBasicSettingData(class USettingConfig_C* ServerSettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.InitBasicSettingData");

	UGlobal_Bp_C_InitBasicSettingData_Params params;
	params.ServerSettingConfig = ServerSettingConfig;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.InitPickupSettingData_XT
// (NetReliable, Event, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        SettingConfig                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::STATIC_InitPickupSettingData_XT(class USettingConfig_C* SettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.InitPickupSettingData_XT");

	UGlobal_Bp_C_InitPickupSettingData_XT_Params params;
	params.SettingConfig = SettingConfig;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.InitPickupSettingData
// (NetReliable, NetRequest, Native, Event, NetResponse, NetServer, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        ServerSettingConfig            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::InitPickupSettingData(class USettingConfig_C* ServerSettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.InitPickupSettingData");

	UGlobal_Bp_C_InitPickupSettingData_Params params;
	params.ServerSettingConfig = ServerSettingConfig;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.InitSensibilitySettingData
// (NetReliable, Exec, Native, Event, NetResponse, NetServer, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        ServerSettingConfig            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::InitSensibilitySettingData(class USettingConfig_C* ServerSettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.InitSensibilitySettingData");

	UGlobal_Bp_C_InitSensibilitySettingData_Params params;
	params.ServerSettingConfig = ServerSettingConfig;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.SetGrenadeDefaultPickValue
// (Net, NetReliable, NetRequest, Event, NetResponse, Protected, NetServer, HasOutParms, HasDefaults, NetClient, DLLImport, BlueprintEvent, BlueprintPure, Const)

void UGlobal_Bp_C::SetGrenadeDefaultPickValue()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.SetGrenadeDefaultPickValue");

	UGlobal_Bp_C_SetGrenadeDefaultPickValue_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.InitMapFromCBToES
// (NetReliable, Native, NetResponse, NetMulticast, NetServer, BlueprintCallable, BlueprintEvent)

void UGlobal_Bp_C::InitMapFromCBToES()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.InitMapFromCBToES");

	UGlobal_Bp_C_InitMapFromCBToES_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.MapFromCBToESGlobal
// (Exec, Event, NetResponse, Static, NetMulticast, NetServer, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        SettingConfig                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::STATIC_MapFromCBToESGlobal(class USettingConfig_C* SettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.MapFromCBToESGlobal");

	UGlobal_Bp_C_MapFromCBToESGlobal_Params params;
	params.SettingConfig = SettingConfig;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.MapFromCBToESJK
// (NetReliable, NetRequest, Event, NetResponse, Static, NetServer, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        SettingConfig                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::STATIC_MapFromCBToESJK(class USettingConfig_C* SettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.MapFromCBToESJK");

	UGlobal_Bp_C_MapFromCBToESJK_Params params;
	params.SettingConfig = SettingConfig;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.MapFromCBToESVN
// (NetRequest, Exec, Native, NetResponse, Static, NetServer, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USettingConfig_C*        SettingConfig                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::STATIC_MapFromCBToESVN(class USettingConfig_C* SettingConfig)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.MapFromCBToESVN");

	UGlobal_Bp_C_MapFromCBToESVN_Params params;
	params.SettingConfig = SettingConfig;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.LoadSettingConfigFromSlot
// (Event, NetResponse, Static, NetServer, BlueprintCallable, BlueprintEvent)

void UGlobal_Bp_C::STATIC_LoadSettingConfigFromSlot()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.LoadSettingConfigFromSlot");

	UGlobal_Bp_C_LoadSettingConfigFromSlot_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.UpdateBigHandOperateRedPoint
// (NetRequest, Native, NetResponse, Static, NetServer, BlueprintCallable, BlueprintEvent)

void UGlobal_Bp_C::STATIC_UpdateBigHandOperateRedPoint()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.UpdateBigHandOperateRedPoint");

	UGlobal_Bp_C_UpdateBigHandOperateRedPoint_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.SetPostProcessSettings
// (Net, NetReliable, Event, NetResponse, Protected, NetServer, HasOutParms, HasDefaults, NetClient, DLLImport, BlueprintEvent, BlueprintPure, Const)
// Parameters:
// int                            ID                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Time                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           isReverse                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           isClosing                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::SetPostProcessSettings(int ID, float Time, bool isReverse, bool isClosing)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.SetPostProcessSettings");

	UGlobal_Bp_C_SetPostProcessSettings_Params params;
	params.ID = ID;
	params.Time = Time;
	params.isReverse = isReverse;
	params.isClosing = isClosing;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.ShowItemPreviewPress
// ()

void UGlobal_Bp_C::ShowItemPreviewPress()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.ShowItemPreviewPress");

	UGlobal_Bp_C_ShowItemPreviewPress_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.ShowItemPreviewClick
// (Net, NetRequest, Event, NetResponse, Protected, NetServer, HasOutParms, HasDefaults, NetClient, DLLImport, BlueprintEvent, BlueprintPure, Const)
// Parameters:
// int                            ItemId                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::ShowItemPreviewClick(int ItemId)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.ShowItemPreviewClick");

	UGlobal_Bp_C_ShowItemPreviewClick_Params params;
	params.ItemId = ItemId;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.SaveAnniversaryNeedShow
// (Exec, Event, Static, NetMulticast, NetServer, BlueprintCallable, BlueprintEvent)

void UGlobal_Bp_C::STATIC_SaveAnniversaryNeedShow()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.SaveAnniversaryNeedShow");

	UGlobal_Bp_C_SaveAnniversaryNeedShow_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.GetAnniversaryNeedShow
// ()

void UGlobal_Bp_C::GetAnniversaryNeedShow()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.GetAnniversaryNeedShow");

	UGlobal_Bp_C_GetAnniversaryNeedShow_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.SaveResidentEvilNeedShow
// (NetReliable, Exec, Native, Event, NetResponse, NetMulticast, NetServer, BlueprintCallable, BlueprintEvent)

void UGlobal_Bp_C::SaveResidentEvilNeedShow()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.SaveResidentEvilNeedShow");

	UGlobal_Bp_C_SaveResidentEvilNeedShow_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.GetResidentEvilNeedShow
// ()

void UGlobal_Bp_C::GetResidentEvilNeedShow()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.GetResidentEvilNeedShow");

	UGlobal_Bp_C_GetResidentEvilNeedShow_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.SaveChristmasNeedShow
// (Exec, Native, Event, NetResponse, NetMulticast, NetServer, BlueprintCallable, BlueprintEvent)

void UGlobal_Bp_C::SaveChristmasNeedShow()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.SaveChristmasNeedShow");

	UGlobal_Bp_C_SaveChristmasNeedShow_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.GetChristmasNeedShow
// ()

void UGlobal_Bp_C::GetChristmasNeedShow()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.GetChristmasNeedShow");

	UGlobal_Bp_C_GetChristmasNeedShow_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.GetDragDropWidget
// (Net, NetRequest, Exec, Event, NetResponse, Static, NetMulticast, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            dragDropType                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::STATIC_GetDragDropWidget(int dragDropType)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.GetDragDropWidget");

	UGlobal_Bp_C_GetDragDropWidget_Params params;
	params.dragDropType = dragDropType;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.GetRankTexture
// (NetRequest, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            rankIntegral                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTexture2D*              Output                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::GetRankTexture(int rankIntegral, class UTexture2D** Output)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.GetRankTexture");

	UGlobal_Bp_C_GetRankTexture_Params params;
	params.rankIntegral = rankIntegral;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Output != nullptr)
		*Output = params.Output;
}


// Function Global_Bp.Global_Bp_C.GetCorpsIconTexture
// (NetReliable, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            IconID                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTexture2D*              Value                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::GetCorpsIconTexture(int IconID, class UTexture2D** Value)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.GetCorpsIconTexture");

	UGlobal_Bp_C_GetCorpsIconTexture_Params params;
	params.IconID = IconID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Value != nullptr)
		*Value = params.Value;
}


// Function Global_Bp.Global_Bp_C.GetFrameTexture
// (NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            frameLevel                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTexture2D*              Output                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::GetFrameTexture(int frameLevel, class UTexture2D** Output)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.GetFrameTexture");

	UGlobal_Bp_C_GetFrameTexture_Params params;
	params.frameLevel = frameLevel;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Output != nullptr)
		*Output = params.Output;
}


// Function Global_Bp.Global_Bp_C.EventAndroidQuitGame
// (NetReliable, NetRequest, Exec, Event, NetResponse, NetMulticast, Protected, Delegate, HasOutParms, NetClient, DLLImport, BlueprintEvent, BlueprintPure, Const)

void UGlobal_Bp_C::EventAndroidQuitGame()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.EventAndroidQuitGame");

	UGlobal_Bp_C_EventAndroidQuitGame_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.EnterLogin
// (NetRequest, Event, NetResponse, NetMulticast, Protected, Delegate, HasOutParms, NetClient, DLLImport, BlueprintEvent, BlueprintPure, Const)

void UGlobal_Bp_C::EnterLogin()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.EnterLogin");

	UGlobal_Bp_C_EnterLogin_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.RecoverMaxFps
// ()

void UGlobal_Bp_C::RecoverMaxFps()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.RecoverMaxFps");

	UGlobal_Bp_C_RecoverMaxFps_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.Construct
// ()

void UGlobal_Bp_C::Construct()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.Construct");

	UGlobal_Bp_C_Construct_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Global_Bp.Global_Bp_C.ExecuteUbergraph_Global_Bp
// (NetRequest, Exec, Native, Event, NetResponse, Protected, NetServer, HasOutParms, HasDefaults, NetClient, DLLImport, BlueprintEvent, BlueprintPure, Const)
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UGlobal_Bp_C::ExecuteUbergraph_Global_Bp(int EntryPoint)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Global_Bp.Global_Bp_C.ExecuteUbergraph_Global_Bp");

	UGlobal_Bp_C_ExecuteUbergraph_Global_Bp_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

