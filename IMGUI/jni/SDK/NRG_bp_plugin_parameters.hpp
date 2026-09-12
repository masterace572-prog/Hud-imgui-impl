#pragma once

// PUBG MOBILE (2.8.1) SDKGen by @TEAMNRG1 | @TeamNRG_MOD | (NRG Owner: @TMNrgOwnerBot)
#include "../SDK.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function bp_plugin.bp_pluginBPLibrary.bp_pluginSendEvent
struct Ubp_pluginBPLibrary_bp_pluginSendEvent_Params
{
	struct FString                                     jsonEventCmd;                                             // (Parm, ZeroConstructor)
};

// Function bp_plugin.bp_pluginBPLibrary.bp_pluginLaunchMeemoFunction
struct Ubp_pluginBPLibrary_bp_pluginLaunchMeemoFunction_Params
{
	struct FString                                     Param;                                                    // (Parm, ZeroConstructor)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function bp_plugin.bp_pluginBPLibrary.bp_pluginIsInForeground
struct Ubp_pluginBPLibrary_bp_pluginIsInForeground_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

