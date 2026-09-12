#pragma once

// PUBG MOBILE (2.8.1) SDKGen by @TEAMNRG1 | @TeamNRG_MOD | (NRG Owner: @TMNrgOwnerBot)
namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass GlobalUIEventDispatcher_BP.GlobalUIEventDispatcher_BP_C
// 0x0010 (0x0038 - 0x0028)
class UGlobalUIEventDispatcher_BP_C : public UObject
{
public:
	struct FScriptMulticastDelegate                    WardrobePutDownEvent;                                     // 0x0028(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass GlobalUIEventDispatcher_BP.GlobalUIEventDispatcher_BP_C");
		return pStaticClass;
	}


	void STATIC_WardrobePutDownEvent__DelegateSignature(int PutonID, int resID);
};


}

