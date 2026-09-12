// PUBG MOBILE (2.8.1) SDKGen by @TEAMNRG1 | @TeamNRG_MOD | (NRG Owner: @TMNrgOwnerBot)
#include "../SDK.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.IsSegmentStarSwitchOpen
// (NetReliable, NetRequest, Event, NetResponse, Static, NetMulticast, Public, Protected, HasOutParms, DLLImport, BlueprintEvent, Const, NetValidate)
// Parameters:
// bool                           isStarOpen                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::STATIC_IsSegmentStarSwitchOpen(bool* isStarOpen)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.IsSegmentStarSwitchOpen");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_IsSegmentStarSwitchOpen_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	if (isStarOpen != nullptr)
		*isStarOpen = params.isStarOpen;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetArenaRankInteralWithCustomColor
// (Net, NetRequest, Native, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            RankInteral                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTextBlock*              TextIntegralName               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSlateColor             Color                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::SetArenaRankInteralWithCustomColor(int RankInteral, class UTextBlock* TextIntegralName, const struct FSlateColor& Color)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetArenaRankInteralWithCustomColor");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_SetArenaRankInteralWithCustomColor_Params params;
	params.RankInteral = RankInteral;
	params.TextIntegralName = TextIntegralName;
	params.Color = Color;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteralBySeason
// (Net, NetReliable, Native, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            rankIntegral                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTextBlock*              TextIntegralName               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            SeasonID                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::SetRankInteralBySeason(int rankIntegral, class UTextBlock* TextIntegralName, int SeasonID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteralBySeason");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_SetRankInteralBySeason_Params params;
	params.rankIntegral = rankIntegral;
	params.TextIntegralName = TextIntegralName;
	params.SeasonID = SeasonID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankCustomColor
// (NetReliable, Native, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            rankIntegral                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTextBlock*              TextIntegralName               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSlateColor             Color                          (BlueprintVisible, BlueprintReadOnly, Parm)
// int                            SeasonID                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::SetRankCustomColor(int rankIntegral, class UTextBlock* TextIntegralName, const struct FSlateColor& Color, int SeasonID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankCustomColor");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_SetRankCustomColor_Params params;
	params.rankIntegral = rankIntegral;
	params.TextIntegralName = TextIntegralName;
	params.Color = Color;
	params.SeasonID = SeasonID;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteralJaguar
// (Native, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            rankIntegral                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTextBlock*              TextIntegralName               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::SetRankInteralJaguar(int rankIntegral, class UTextBlock* TextIntegralName)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteralJaguar");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_SetRankInteralJaguar_Params params;
	params.rankIntegral = rankIntegral;
	params.TextIntegralName = TextIntegralName;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteral
// (NetReliable, NetRequest, Exec, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            rankIntegral                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTextBlock*              TextIntegralName               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::SetRankInteral(int rankIntegral, class UTextBlock* TextIntegralName)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteral");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_SetRankInteral_Params params;
	params.rankIntegral = rankIntegral;
	params.TextIntegralName = TextIntegralName;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteralInXMission
// (NetRequest, Exec, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            rankIntegral                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTextBlock*              TextIntegralName               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::SetRankInteralInXMission(int rankIntegral, class UTextBlock* TextIntegralName)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteralInXMission");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_SetRankInteralInXMission_Params params;
	params.rankIntegral = rankIntegral;
	params.TextIntegralName = TextIntegralName;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetArenaRankInteral
// (Net, NetReliable, Exec, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            rankIntegral                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTextBlock*              TextIntegralName               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::SetArenaRankInteral(int rankIntegral, class UTextBlock* TextIntegralName)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetArenaRankInteral");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_SetArenaRankInteral_Params params;
	params.rankIntegral = rankIntegral;
	params.TextIntegralName = TextIntegralName;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteralCommon
// (Net, Exec, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            rankIntegral                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTextBlock*              TextIntegralName               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            SeasonID                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::SetRankInteralCommon(int rankIntegral, class UTextBlock* TextIntegralName, int SeasonID)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.SetRankInteralCommon");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_SetRankInteralCommon_Params params;
	params.rankIntegral = rankIntegral;
	params.TextIntegralName = TextIntegralName;
	params.SeasonID = SeasonID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.PreConstruct
// (NetRequest, Event, NetResponse, Static, NetMulticast, Public, Protected, HasOutParms, DLLImport, BlueprintEvent, Const, NetValidate)
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::STATIC_PreConstruct(bool* IsDesignTime)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.PreConstruct");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.Construct
// ()

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::Construct()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.Construct");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_Construct_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.ConstructItem
// ()

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::ConstructItem()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.ConstructItem");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_ConstructItem_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.Destruct
// ()

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::Destruct()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.Destruct");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_Destruct_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.ExecuteUbergraph_Common_RankIntegralLevel_Style_Small_UIBP
// (Net, NetReliable, NetRequest, NetMulticast, MulticastDelegate, Private, NetServer, NetClient, DLLImport)
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_RankIntegralLevel_Style_Small_UIBP_C::ExecuteUbergraph_Common_RankIntegralLevel_Style_Small_UIBP(int EntryPoint)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_RankIntegralLevel_Style_Small_UIBP.Common_RankIntegralLevel_Style_Small_UIBP_C.ExecuteUbergraph_Common_RankIntegralLevel_Style_Small_UIBP");

	UCommon_RankIntegralLevel_Style_Small_UIBP_C_ExecuteUbergraph_Common_RankIntegralLevel_Style_Small_UIBP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

