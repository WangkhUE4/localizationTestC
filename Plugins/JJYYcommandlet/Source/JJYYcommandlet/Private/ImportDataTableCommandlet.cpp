// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ImportDataTableCommandlet.h"
#include "JJYYcommandlet.h"

#include "AssetRegistryModule.h"
#include "Engine/Public/Internationalization\StringTable.h"
#include "Core/Public/Internationalization\StringTableCore.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "UnrealEd\Public\PackageHelperFunctions.h"
#include <Misc/FileHelper.h>
#include <Kismet/KismetSystemLibrary.h>

UImportDataTableCommandlet::UImportDataTableCommandlet()
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

//-run=ImportStringTable -PreProcessFileName="PreProcessDataTable.py" -ImportDataFileName="ImportDataTable.py"

int32 UImportDataTableCommandlet::Main(const FString& Params)
{


	InitCommandLine(Params);
	FString command = FString(TEXT("py ")) + FPaths::ProjectDir() + "Script/DataTable/";
	UKismetSystemLibrary::ExecuteConsoleCommand(this, command + PreProcessFileName);
	UKismetSystemLibrary::ExecuteConsoleCommand(this, command + ImportDataFileName);
	
	return 0;
}

void UImportDataTableCommandlet::InitCommandLine(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> SwitchParams;
	ParseCommandLine(*Params, Tokens, Switches, SwitchParams);


	if (SwitchParams.Contains(TEXT("PreProcessFileName")))
	{
		PreProcessFileName = SwitchParams[TEXT("PreProcessFileName")];
		UE_LOG(logJJYYcommandlet, Display, TEXT("PreProcessFileName:%s"), *PreProcessFileName);
		ImportDataFileName = SwitchParams[TEXT("ImportDataFileName")];
		UE_LOG(logJJYYcommandlet, Display, TEXT("ImportDataFileName:%s"), *ImportDataFileName);
	}

}
