#pragma once

// PUBG MOBILE (2.8.1) SDKGen by @TEAMNRG1 | @TeamNRG_MOD | (NRG Owner: @TMNrgOwnerBot)
#include "../SDK.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function AndroidPermission.AndroidPermissionFunctionLibrary.CheckPermission
struct UAndroidPermissionFunctionLibrary_CheckPermission_Params
{
	struct FString                                     permission;                                               // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AndroidPermission.AndroidPermissionFunctionLibrary.AcquirePermissions
struct UAndroidPermissionFunctionLibrary_AcquirePermissions_Params
{
	TArray<struct FString>                             Permissions;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	class UAndroidPermissionCallbackProxy*             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

