// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ExportDataTableCommandlet.h"
#include "JJYYcommandlet.h"
#include "Misc/Paths.h"
#include "Misc\FileHelper.h"
#include "Serialization\JsonReader.h"
#include "Dom\JsonObject.h"
#include "Serialization\JsonSerializer.h"
#include "Engine/DataTable.h"
#include <string>


UExportDataTableCommandlet::UExportDataTableCommandlet()
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

int32 UExportDataTableCommandlet::Main(const FString& Params)
{
	configDatas.Empty();

	FString configPath = FPaths::Combine(FPaths::ProjectDir(), TEXT(R"=(Script\DataTable\outPutScript\config.json)="));
	FString userSettingPath = FPaths::Combine(FPaths::ProjectDir(), TEXT(R"=(Script\DataTable\outPutScript\userSetting.json)="));
	FString outputPath = FPaths::Combine(FPaths::ProjectDir(), TEXT(R"=(Script\DataTable\outPutScript\output\)="));

	FString configContent;
	FString userSettingContent;

	if (!FFileHelper::LoadFileToString(configContent, *configPath))
	{
		UE_LOG(logJJYYcommandlet, Display, TEXT("%s read failed"), *configPath);
		return -1;
	}
		
	if (!FFileHelper::LoadFileToString(userSettingContent, *userSettingPath))
	{
		UE_LOG(logJJYYcommandlet, Display, TEXT("%s read failed"), *userSettingPath);
		return -1;
	}

	TSharedRef<TJsonReader<>> configJsonReader = TJsonReaderFactory<>::Create(configContent);
	TArray< TSharedPtr<FJsonValue> > configRootArr;
	if (FJsonSerializer::Deserialize(configJsonReader, configRootArr))
	{
		for (auto& i: configRootArr)
		{
			const TSharedPtr<FJsonObject> iObj = i->AsObject();
			ExportDataTableconfig temp;
			temp.name = iObj->GetStringField("name");
			temp.path = iObj->GetStringField("path");
			configDatas.Emplace(temp);
		}
	}


	TSharedRef<TJsonReader<>> userSettingJsonReader = TJsonReaderFactory<>::Create(userSettingContent);
	TSharedPtr<FJsonObject> userSettingRootObject;
	if (FJsonSerializer::Deserialize(userSettingJsonReader, userSettingRootObject) && userSettingRootObject.IsValid())
	{
		SaveConfigToBin(configContent,outputPath);

		bool ExportAll = userSettingRootObject->GetBoolField("ExportAll");
		TArray<FString> ExportNames;
		userSettingRootObject->TryGetStringArrayField("ExportNames", ExportNames);
		if (ExportAll)
		{
			for (auto& data : configDatas)
			{

				LoadAndSave(data, outputPath);

			}
		}
		else
		{
			for (auto& exprotName : ExportNames)
			{
				auto data = configDatas.FindByPredicate(
					[&exprotName](const ExportDataTableconfig& data) {
						return data.name == exprotName;
					});
				if (data)
				{
					LoadAndSave(*data, outputPath);
				}
			}
		}
	}

	return 0;
	
}


void UExportDataTableCommandlet::SaveConfigToBin(FString& configStr, FString& outputPath)
{
	//Code(configStr);
	FFileHelper::SaveStringToFile(configStr, *(outputPath + TEXT("ImportPcTableConfig.bin")), FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	//Decode(configStr);
	//FFileHelper::SaveStringToFile(configStr, *(outputPath + TEXT("ImportTableConfig.csv")));
}

void UExportDataTableCommandlet::LoadAndSave(ExportDataTableconfig& data, FString& outputPath)
{
	auto m_table = LoadObject<UDataTable>(nullptr, *data.path);
	FString str = m_table->GetTableAsCSV();
	//Code(str);
	FFileHelper::SaveStringToFile(str, *(outputPath + data.name + TEXT("_PC.bin")), FFileHelper::EEncodingOptions::ForceUTF8);
	//Decode(str);
	//FFileHelper::SaveStringToFile(str, *(outputPath + data.name + TEXT(".csv")));
}

void UExportDataTableCommandlet::Code(FString& sourceStr, int32 step /*= 1*/)
{
	int32 i = 0;
	for (auto& ch : sourceStr)
	{
		ch = ch ^ (uint8)(i * step);
		i++;
	}
}

void UExportDataTableCommandlet::Decode(FString& sourceStr, int32 step /*= 1*/)
{
	int32 i = 0;
	for (auto& ch : sourceStr)
	{
		ch = ch ^ (uint8)(i * step);
		i++;
	}
}

