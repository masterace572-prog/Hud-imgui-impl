#pragma once

// PUBG MOBILE (2.8.1) SDKGen by @TEAMNRG1 | @TeamNRG_MOD | (NRG Owner: @TMNrgOwnerBot)
namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class GooglePAD.GooglePADFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class UGooglePADFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class GooglePAD.GooglePADFunctionLibrary");
		return pStaticClass;
	}


	EGooglePADErrorCode ShowCellularDataConfirmation();
	EGooglePADErrorCode RequestRemoval(const struct FString& Name);
	EGooglePADErrorCode RequestInfo(TArray<struct FString> AssetPacks);
	EGooglePADErrorCode RequestDownload(TArray<struct FString> AssetPacks);
	void ReleaseDownloadState(int State);
	void ReleaseAssetPackLocation(int Location);
	int GetTotalBytesToDownload(int State);
	EGooglePADStorageMethod GetStorageMethod(int Location);
	EGooglePADErrorCode GetShowCellularDataConfirmationStatus(EGooglePADCellularDataConfirmStatus* Status);
	EGooglePADDownloadStatus GetDownloadStatus(int State);
	EGooglePADErrorCode GetDownloadState(const struct FString& Name, int* State);
	int GetBytesDownloaded(int State);
	struct FString GetAssetsPath(int Location);
	EGooglePADErrorCode GetAssetPackLocation(const struct FString& Name, int* Location);
	EGooglePADErrorCode CancelDownload(TArray<struct FString> AssetPacks);
};


}

