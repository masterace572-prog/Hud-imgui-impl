#pragma once

// PUBG MOBILE (2.8.1) SDKGen by @TEAMNRG1 | @TeamNRG_MOD | (NRG Owner: @TMNrgOwnerBot)
namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class OMobileFBPL.OMobileFBPL
// 0x0000 (0x0028 - 0x0028)
class UOMobileFBPL : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class OMobileFBPL.OMobileFBPL");
		return pStaticClass;
	}


	bool IsRunningOnBattery();
	bool IsBatteryStateCharging();
	int GetVolumeState();
	struct FString GetDeviceName();
	float GetBatteryTemperature();
	int GetBatteryLevel();
	bool AreHeadphonesPluggedIn();
};


}

