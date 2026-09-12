#pragma once

// PUBG MOBILE (2.8.1) SDKGen by @TEAMNRG1 | @TeamNRG_MOD | (NRG Owner: @TMNrgOwnerBot)
namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum ClientNet.EIMSDKPlatformType
enum class EIMSDKPlatformType : uint8_t
{
	EIMSDKPlatformType__kIMSDKPlatformTypeUnknow = 0,
	EIMSDKPlatformType__kIMSDKPlatformTypeIOS = 1,
	EIMSDKPlatformType__kIMSDKPlatformTypeAndroid = 2,
	EIMSDKPlatformType__EIMSDKPlatformType_MAX = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct ClientNet.IMSDKExtraInfo
// 0x0050
struct FIMSDKExtraInfo
{
	TMap<struct FString, struct FString>               ExtraInfo;                                                // 0x0000(0x0050) (ZeroConstructor)
};

}

