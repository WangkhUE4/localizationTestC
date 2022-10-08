// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ImportStringTableCommandlet.h"
#include "JJYYcommandlet.h"

#include "AssetRegistryModule.h"
#include "Engine/Public/Internationalization\StringTable.h"
#include "Core/Public/Internationalization\StringTableCore.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "UnrealEd\Public\PackageHelperFunctions.h"

UImportStringTableCommandlet::UImportStringTableCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}


//	D:\UE4Engine\UE_4.24\Engine\Binaries\Win64\UE4Editor - Cmd.exe 
//	D:\UE4Project\AutomationTestDemo\AutomationTestDemo.uproject 
//	-run  = ImportStringTable 
//	-From = "D:/UE4Project/AutomationTestDemo/123.csv" 
//	-To   = "/Game/ssss"

int32 UImportStringTableCommandlet::Main(const FString& Params)
{


	InitCommandLine(Params);

	FindAssetList.Empty();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);

	//AssetRegistryModule.Get().GetAssetsByPackageName(FName("/Game/ssss"), FindAssetList);
	
	AssetRegistryModule.Get().GetAssetsByPackageName(FName(*To), FindAssetList);

	if (FindAssetList.Num() == 0)
	{
		UE_LOG(logJJYYcommandlet, Error, TEXT("FindAssetList.Num() == 0"));
		return 1;
	}
	UPackage* package = FindAssetList[0].GetPackage();
	UStringTable* StringTable = Cast<UStringTable>(FindAssetList[0].GetAsset());
	if (StringTable)
	{
		StringTable->Modify();
		//StringTable->GetMutableStringTable()->ImportStrings("D:/UE4Project/AutomationTestDemo/123.csv");
		StringTable->GetMutableStringTable()->ImportStrings(From);
		TArray<UPackage*> PackagesToSave;
		PackagesToSave.Add(package);
		//FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, false, false);
		GEditor->SavePackage(package, nullptr, RF_Standalone, *package->FileName.ToString(), (FOutputDevice*)GWarn);
		package->SetDirtyFlag(true);
		//FEditorFileUtils::SaveDirtyPackages(false, false, true,true);
		TArray<UClass*> saveclass;
		saveclass.Add(UStringTable::StaticClass());
		FEditorFileUtils::SaveDirtyContentPackages(saveclass, false, true, false, false);
		UE_LOG(logJJYYcommandlet, Display, TEXT("-------------------------ImportStringTableSuccess--------------------------"));

	}
	
	return 0;
}

void UImportStringTableCommandlet::InitCommandLine(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> SwitchParams;
	ParseCommandLine(*Params, Tokens, Switches, SwitchParams);


	if (SwitchParams.Contains(TEXT("From")))
	{
		From = SwitchParams[TEXT("From")];
		UE_LOG(logJJYYcommandlet, Display, TEXT("From:%s"),*From);

	}

	if (SwitchParams.Contains(TEXT("To")))
	{
		To = SwitchParams[TEXT("To")];
		UE_LOG(logJJYYcommandlet, Display, TEXT("To:%s"), *To);
	}
}
