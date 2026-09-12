// PUBG MOBILE (2.8.1) SDKGen by @TEAMNRG1 | @TeamNRG_MOD | (NRG Owner: @TMNrgOwnerBot)
#include "../SDK.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function PlayerPrefs.PlayerPrefs_C.SetPopupPolicyVersion
// (Net, NetReliable, Exec, Native, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            PolicyVersion                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetPopupPolicyVersion(int PolicyVersion)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetPopupPolicyVersion");

	UPlayerPrefs_C_SetPopupPolicyVersion_Params params;
	params.PolicyVersion = PolicyVersion;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetGuaranteeFlag
// (NetReliable, Exec, Native, Event, NetResponse, MulticastDelegate, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool                           clicked                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetGuaranteeFlag(bool clicked)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetGuaranteeFlag");

	UPlayerPrefs_C_SetGuaranteeFlag_Params params;
	params.clicked = clicked;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.GetGuaranteeClickFlag
// (Native, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool                           clicked                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::STATIC_GetGuaranteeClickFlag(bool* clicked)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetGuaranteeClickFlag");

	UPlayerPrefs_C_GetGuaranteeClickFlag_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (clicked != nullptr)
		*clicked = params.clicked;
}


// Function PlayerPrefs.PlayerPrefs_C.GetDecomposeIndexTriggerTime
// (NetReliable, Exec, Native, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            DecomposeTriggerTim            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetDecomposeIndexTriggerTime(int* DecomposeTriggerTim)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetDecomposeIndexTriggerTime");

	UPlayerPrefs_C_GetDecomposeIndexTriggerTime_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (DecomposeTriggerTim != nullptr)
		*DecomposeTriggerTim = params.DecomposeTriggerTim;
}


// Function PlayerPrefs.PlayerPrefs_C.SetDecomposeIndexTriggerTime
// (Exec, Native, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            TimeStamp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetDecomposeIndexTriggerTime(int TimeStamp)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetDecomposeIndexTriggerTime");

	UPlayerPrefs_C_SetDecomposeIndexTriggerTime_Params params;
	params.TimeStamp = TimeStamp;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetClickTimeAnniversary
// (NetReliable, NetRequest, Native, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// int                            Time                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetClickTimeAnniversary(const struct FString& UID, int Time)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetClickTimeAnniversary");

	UPlayerPrefs_C_SetClickTimeAnniversary_Params params;
	params.UID = UID;
	params.Time = Time;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.GetClickTimeAnniversary
// (NetRequest, Native, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// int                            Value                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetClickTimeAnniversary(const struct FString& UID, int* Value)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetClickTimeAnniversary");

	UPlayerPrefs_C_GetClickTimeAnniversary_Params params;
	params.UID = UID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Value != nullptr)
		*Value = params.Value;
}


// Function PlayerPrefs.PlayerPrefs_C.GetCliickVehicleAcitivtyGuideExchange
// (Net, NetReliable, Native, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 Key                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// bool                           hasClick                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetCliickVehicleAcitivtyGuideExchange(const struct FString& Key, bool* hasClick)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetCliickVehicleAcitivtyGuideExchange");

	UPlayerPrefs_C_GetCliickVehicleAcitivtyGuideExchange_Params params;
	params.Key = Key;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (hasClick != nullptr)
		*hasClick = params.hasClick;
}


// Function PlayerPrefs.PlayerPrefs_C.SetCliickVehicleAcitivtyGuideExchange
// (Net, Native, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 Key                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// bool                           isClick                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetCliickVehicleAcitivtyGuideExchange(const struct FString& Key, bool isClick)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetCliickVehicleAcitivtyGuideExchange");

	UPlayerPrefs_C_SetCliickVehicleAcitivtyGuideExchange_Params params;
	params.Key = Key;
	params.isClick = isClick;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetClickTimeIceLucky
// (Net, NetReliable, NetRequest, Exec, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            Time                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::SetClickTimeIceLucky(int Time, const struct FString& UUID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetClickTimeIceLucky");

	UPlayerPrefs_C_SetClickTimeIceLucky_Params params;
	params.Time = Time;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.GetClickTimeIceLucky
// (Net, NetRequest, Exec, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// int                            Value                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetClickTimeIceLucky(const struct FString& UUID, int* Value)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetClickTimeIceLucky");

	UPlayerPrefs_C_GetClickTimeIceLucky_Params params;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Value != nullptr)
		*Value = params.Value;
}


// Function PlayerPrefs.PlayerPrefs_C.SetIsVNGAdult
// (Static, MulticastDelegate, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)

void UPlayerPrefs_C::STATIC_SetIsVNGAdult()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetIsVNGAdult");

	UPlayerPrefs_C_SetIsVNGAdult_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetHasClickHalloweenExchange
// (NetReliable, Event, NetResponse, MulticastDelegate, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool                           isClick                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::SetHasClickHalloweenExchange(bool isClick, const struct FString& UUID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetHasClickHalloweenExchange");

	UPlayerPrefs_C_SetHasClickHalloweenExchange_Params params;
	params.isClick = isClick;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.GetHasClickHalloweenExchange
// (NetRequest, Exec, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// bool                           hasClick                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetHasClickHalloweenExchange(const struct FString& UUID, bool* hasClick)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetHasClickHalloweenExchange");

	UPlayerPrefs_C_GetHasClickHalloweenExchange_Params params;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (hasClick != nullptr)
		*hasClick = params.hasClick;
}


// Function PlayerPrefs.PlayerPrefs_C.SetClickTimeHalloweenVehicle
// (NetReliable, Exec, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            Time                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::SetClickTimeHalloweenVehicle(int Time, const struct FString& UUID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetClickTimeHalloweenVehicle");

	UPlayerPrefs_C_SetClickTimeHalloweenVehicle_Params params;
	params.Time = Time;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.GetClickTimeHalloweenVehicle
// (Exec, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// int                            Value                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetClickTimeHalloweenVehicle(const struct FString& UUID, int* Value)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetClickTimeHalloweenVehicle");

	UPlayerPrefs_C_GetClickTimeHalloweenVehicle_Params params;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Value != nullptr)
		*Value = params.Value;
}


// Function PlayerPrefs.PlayerPrefs_C.GetFaceInfoClickedIDAndTime
// (NetReliable, NetRequest, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 faceid                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// struct FString                 TimeStamp                      (Parm, OutParm, ZeroConstructor)

void UPlayerPrefs_C::GetFaceInfoClickedIDAndTime(const struct FString& faceid, struct FString* TimeStamp)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetFaceInfoClickedIDAndTime");

	UPlayerPrefs_C_GetFaceInfoClickedIDAndTime_Params params;
	params.faceid = faceid;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (TimeStamp != nullptr)
		*TimeStamp = params.TimeStamp;
}


// Function PlayerPrefs.PlayerPrefs_C.SetFaceInfoClickedIDAndTime
// (Net, NetRequest, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 faceid                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::SetFaceInfoClickedIDAndTime(const struct FString& faceid)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetFaceInfoClickedIDAndTime");

	UPlayerPrefs_C_SetFaceInfoClickedIDAndTime_Params params;
	params.faceid = faceid;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.GetCursorFaceInfoID
// (Net, NetReliable, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            CursorFaceInfoID               (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetCursorFaceInfoID(int* CursorFaceInfoID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetCursorFaceInfoID");

	UPlayerPrefs_C_GetCursorFaceInfoID_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (CursorFaceInfoID != nullptr)
		*CursorFaceInfoID = params.CursorFaceInfoID;
}


// Function PlayerPrefs.PlayerPrefs_C.SetCursorFaceInfoID
// (Net, NetResponse, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            LastFace                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetCursorFaceInfoID(int LastFace)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetCursorFaceInfoID");

	UPlayerPrefs_C_SetCursorFaceInfoID_Params params;
	params.LastFace = LastFace;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetHasClickInviteTeamAct
// (NetReliable, Event, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool                           isClick                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::STATIC_SetHasClickInviteTeamAct(bool isClick, const struct FString& UUID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetHasClickInviteTeamAct");

	UPlayerPrefs_C_SetHasClickInviteTeamAct_Params params;
	params.isClick = isClick;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.GetHasClickInviteTeamAct
// (Net, NetReliable, NetRequest, Exec, Native, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// bool                           hasClick                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetHasClickInviteTeamAct(const struct FString& UUID, bool* hasClick)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetHasClickInviteTeamAct");

	UPlayerPrefs_C_GetHasClickInviteTeamAct_Params params;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (hasClick != nullptr)
		*hasClick = params.hasClick;
}


// Function PlayerPrefs.PlayerPrefs_C.GetHasClickUPassAct
// (NetReliable, NetRequest, Exec, Native, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// bool                           hasClick                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetHasClickUPassAct(const struct FString& UUID, bool* hasClick)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetHasClickUPassAct");

	UPlayerPrefs_C_GetHasClickUPassAct_Params params;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (hasClick != nullptr)
		*hasClick = params.hasClick;
}


// Function PlayerPrefs.PlayerPrefs_C.SetHasClickUPassAct
// (NetRequest, Exec, Native, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool                           isClick                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString                 UUID                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::STATIC_SetHasClickUPassAct(bool isClick, const struct FString& UUID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetHasClickUPassAct");

	UPlayerPrefs_C_SetHasClickUPassAct_Params params;
	params.isClick = isClick;
	params.UUID = UUID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetShowSwitchSecondLanguageNextTime
// (Exec, Event, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FDateTime               DateTime                       (BlueprintVisible, BlueprintReadOnly, Parm)

void UPlayerPrefs_C::STATIC_SetShowSwitchSecondLanguageNextTime(const struct FDateTime& DateTime)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetShowSwitchSecondLanguageNextTime");

	UPlayerPrefs_C_SetShowSwitchSecondLanguageNextTime_Params params;
	params.DateTime = DateTime;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.GetShowSwitchSecondLanguageNextTime
// (Event, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// struct FDateTime               DateTime                       (Parm, OutParm)

void UPlayerPrefs_C::STATIC_GetShowSwitchSecondLanguageNextTime(struct FDateTime* DateTime)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetShowSwitchSecondLanguageNextTime");

	UPlayerPrefs_C_GetShowSwitchSecondLanguageNextTime_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (DateTime != nullptr)
		*DateTime = params.DateTime;
}


// Function PlayerPrefs.PlayerPrefs_C.GetLoginFrequency
// (NetRequest, Exec, Native, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            loginfreq                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetLoginFrequency(int* loginfreq)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetLoginFrequency");

	UPlayerPrefs_C_GetLoginFrequency_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (loginfreq != nullptr)
		*loginfreq = params.loginfreq;
}


// Function PlayerPrefs.PlayerPrefs_C.SetLoginFrequency
// (NetReliable, Exec, Native, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            CurrentDay                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetLoginFrequency(int CurrentDay)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetLoginFrequency");

	UPlayerPrefs_C_SetLoginFrequency_Params params;
	params.CurrentDay = CurrentDay;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.GetAirDropTime
// (Exec, Native, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// int                            outAirDropTime                 (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetAirDropTime(const struct FString& UID, int* outAirDropTime)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetAirDropTime");

	UPlayerPrefs_C_GetAirDropTime_Params params;
	params.UID = UID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (outAirDropTime != nullptr)
		*outAirDropTime = params.outAirDropTime;
}


// Function PlayerPrefs.PlayerPrefs_C.SetAirDropTime
// (Net, NetReliable, NetRequest, Native, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            InTime                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString                 UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::SetAirDropTime(int InTime, const struct FString& UID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetAirDropTime");

	UPlayerPrefs_C_SetAirDropTime_Params params;
	params.InTime = InTime;
	params.UID = UID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetMystery2LastTime
// (NetReliable, Exec, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            Time                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetMystery2LastTime(int Time)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetMystery2LastTime");

	UPlayerPrefs_C_SetMystery2LastTime_Params params;
	params.Time = Time;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetStoreGiftBoxList
// (NetReliable, Native, Event, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// TArray<int>                    BoxList                        (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)

void UPlayerPrefs_C::STATIC_SetStoreGiftBoxList(TArray<int>* BoxList)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetStoreGiftBoxList");

	UPlayerPrefs_C_SetStoreGiftBoxList_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (BoxList != nullptr)
		*BoxList = params.BoxList;
}


// Function PlayerPrefs.PlayerPrefs_C.GetClickTimeAboutBind
// (Net, NetReliable, Native, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// int                            TimeNotBind                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// int                            TimeBind                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::GetClickTimeAboutBind(const struct FString& UID, int* TimeNotBind, int* TimeBind)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.GetClickTimeAboutBind");

	UPlayerPrefs_C_GetClickTimeAboutBind_Params params;
	params.UID = UID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (TimeNotBind != nullptr)
		*TimeNotBind = params.TimeNotBind;
	if (TimeBind != nullptr)
		*TimeBind = params.TimeBind;
}


// Function PlayerPrefs.PlayerPrefs_C.SetClickTimeAboutBind
// (Net, Native, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            TimeNotBind                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            TimeBind                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString                 UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::SetClickTimeAboutBind(int TimeNotBind, int TimeBind, const struct FString& UID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetClickTimeAboutBind");

	UPlayerPrefs_C_SetClickTimeAboutBind_Params params;
	params.TimeNotBind = TimeNotBind;
	params.TimeBind = TimeBind;
	params.UID = UID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.IsEqualCurID
// (Native, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            Ids                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           Has                            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::IsEqualCurID(int Ids, bool* Has)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.IsEqualCurID");

	UPlayerPrefs_C_IsEqualCurID_Params params;
	params.Ids = Ids;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Has != nullptr)
		*Has = params.Has;
}


// Function PlayerPrefs.PlayerPrefs_C.SetNewsIds
// (NetReliable, NetRequest, Exec, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            Ids                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetNewsIds(int Ids)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetNewsIds");

	UPlayerPrefs_C_SetNewsIds_Params params;
	params.Ids = Ids;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetMallSeeDict
// (Net, NetRequest, Static, NetMulticast, MulticastDelegate, Private, Protected, Delegate, HasOutParms, NetClient, DLLImport, BlueprintEvent, BlueprintPure, Const)
// Parameters:
// TMap<int, bool>                Dict                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::STATIC_SetMallSeeDict(TMap<int, bool> Dict)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetMallSeeDict");

	UPlayerPrefs_C_SetMallSeeDict_Params params;
	params.Dict = Dict;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetStoreBosList
// (NetRequest, Event, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// TArray<int>                    BoxList                        (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)

void UPlayerPrefs_C::STATIC_SetStoreBosList(TArray<int>* BoxList)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetStoreBosList");

	UPlayerPrefs_C_SetStoreBosList_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (BoxList != nullptr)
		*BoxList = params.BoxList;
}


// Function PlayerPrefs.PlayerPrefs_C.SetFirstEnterMall
// (NetReliable, NetRequest, Native, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)

void UPlayerPrefs_C::STATIC_SetFirstEnterMall()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetFirstEnterMall");

	UPlayerPrefs_C_SetFirstEnterMall_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetMysteryLastTime
// (Net, NetReliable, NetRequest, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            Time                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetMysteryLastTime(int Time)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetMysteryLastTime");

	UPlayerPrefs_C_SetMysteryLastTime_Params params;
	params.Time = Time;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.RejectUserAgreement
// (Exec, Native, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)

void UPlayerPrefs_C::STATIC_RejectUserAgreement()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.RejectUserAgreement");

	UPlayerPrefs_C_RejectUserAgreement_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.AcceptUserAgreement
// (Net, NetRequest, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            newVersion                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::AcceptUserAgreement(int newVersion)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.AcceptUserAgreement");

	UPlayerPrefs_C_AcceptUserAgreement_Params params;
	params.newVersion = newVersion;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.ServerListClick
// (NetReliable, Exec, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)

void UPlayerPrefs_C::STATIC_ServerListClick()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.ServerListClick");

	UPlayerPrefs_C_ServerListClick_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.HasCloseLocation
// (NetRequest, Exec, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool                           UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           Has                            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::STATIC_HasCloseLocation(bool UID, bool* Has)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.HasCloseLocation");

	UPlayerPrefs_C_HasCloseLocation_Params params;
	params.UID = UID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Has != nullptr)
		*Has = params.Has;
}


// Function PlayerPrefs.PlayerPrefs_C.SetCloseLocation
// (NetRequest, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool                           CloseLocation                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FString                 UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::STATIC_SetCloseLocation(bool CloseLocation, const struct FString& UID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetCloseLocation");

	UPlayerPrefs_C_SetCloseLocation_Params params;
	params.CloseLocation = CloseLocation;
	params.UID = UID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.HasNearByNewTips
// (Net, NetReliable, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// bool                           Has                            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::HasNearByNewTips(const struct FString& UID, bool* Has)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.HasNearByNewTips");

	UPlayerPrefs_C_HasNearByNewTips_Params params;
	params.UID = UID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (Has != nullptr)
		*Has = params.Has;
}


// Function PlayerPrefs.PlayerPrefs_C.SetNearByNewTipsRead
// (NetReliable, Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// struct FString                 UID                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UPlayerPrefs_C::SetNearByNewTipsRead(const struct FString& UID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetNearByNewTipsRead");

	UPlayerPrefs_C_SetNearByNewTipsRead_Params params;
	params.UID = UID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetYXXYRedPoint
// (Event, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            isRed                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetYXXYRedPoint(int isRed)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetYXXYRedPoint");

	UPlayerPrefs_C_SetYXXYRedPoint_Params params;
	params.isRed = isRed;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.AcceptGuestWarning
// (NetReliable, NetRequest, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)

void UPlayerPrefs_C::STATIC_AcceptGuestWarning()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.AcceptGuestWarning");

	UPlayerPrefs_C_AcceptGuestWarning_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.RejectPolicy
// (NetReliable, NetRequest, Exec, Native, Event, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)

void UPlayerPrefs_C::STATIC_RejectPolicy()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.RejectPolicy");

	UPlayerPrefs_C_RejectPolicy_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.AcceptPolicy
// (NetReliable, NetRequest, Exec, Native, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            newVersion                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::AcceptPolicy(int newVersion)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.AcceptPolicy");

	UPlayerPrefs_C_AcceptPolicy_Params params;
	params.newVersion = newVersion;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetFirstInLobby
// (NetReliable, NetRequest, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)

void UPlayerPrefs_C::STATIC_SetFirstInLobby()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetFirstInLobby");

	UPlayerPrefs_C_SetFirstInLobby_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetTime
// (NetRequest, Exec, Native, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            arg                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetTime(int arg)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetTime");

	UPlayerPrefs_C_SetTime_Params params;
	params.arg = arg;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.ClearCount
// (NetReliable, Exec, Native, Event, NetResponse, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)

void UPlayerPrefs_C::ClearCount()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.ClearCount");

	UPlayerPrefs_C_ClearCount_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.SetCount
// (Net, NetReliable, Exec, Native, Public, Protected, NetServer, HasDefaults, DLLImport, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// int                            Count                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::SetCount(int Count)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SetCount");

	UPlayerPrefs_C_SetCount_Params params;
	params.Count = Count;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function PlayerPrefs.PlayerPrefs_C.LoadData
// (NetRequest, Native, Event, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class USaveGame*               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class USaveGame* UPlayerPrefs_C::STATIC_LoadData()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.LoadData");

	UPlayerPrefs_C_LoadData_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function PlayerPrefs.PlayerPrefs_C.SaveData
// (NetReliable, NetRequest, Exec, Event, NetResponse, Static, NetMulticast, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// bool                           SaveDataState                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UPlayerPrefs_C::STATIC_SaveData(bool* SaveDataState)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PlayerPrefs.PlayerPrefs_C.SaveData");

	UPlayerPrefs_C_SaveData_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (SaveDataState != nullptr)
		*SaveDataState = params.SaveDataState;
}


}

