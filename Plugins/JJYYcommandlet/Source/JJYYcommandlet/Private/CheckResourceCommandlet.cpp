// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CheckResourceCommandlet.h"
#include "JJYYcommandlet.h"

#include "AssetRegistryModule.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "UnrealEd\Public\PackageHelperFunctions.h"

UCheckResourceCommandlet::UCheckResourceCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}


//	D:\UE4Engine\UE_4.24\Engine\Binaries\Win64\UE4Editor - Cmd.exe 
//	D:\UE4Project\AutomationTestDemo\AutomationTestDemo.uproject 
//  -TREATLOADWARNINGSASERRORS
//	-run  = CheckResource 
//	-path="/Game"

int32 UCheckResourceCommandlet::Main(const FString& Params)
{

	InitCommandLine(Params);

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);

	for (auto& _path:paths)
	{
		FindAssetList.Empty();
		AssetRegistryModule.Get().GetAssetsByPath(FName(*_path), FindAssetList, true, true);
		for (auto& asset : FindAssetList)
		{
			asset.GetPackage();
		}
	}
	
	return 0;
}

void UCheckResourceCommandlet::InitCommandLine(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> SwitchParams;
	ParseCommandLine(*Params, Tokens, Switches, SwitchParams);


	if (SwitchParams.Contains(TEXT("path")))
	{
		path = SwitchParams[TEXT("path")];
		UE_LOG(logJJYYcommandlet, Display, TEXT("path:%s"),*path);
		path.ParseIntoArray(paths, TEXT(","));
	}
}
