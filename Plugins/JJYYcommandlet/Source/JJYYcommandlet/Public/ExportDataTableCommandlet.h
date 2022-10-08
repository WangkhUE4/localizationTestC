// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Commandlets/Commandlet.h"
#include "ExportDataTableCommandlet.generated.h"


UCLASS()
class UExportDataTableCommandlet
	: public UCommandlet
{
	GENERATED_BODY()
private:
	struct  ExportDataTableconfig
	{
		FString name;
		FString path;
	};
public:

	/** Default constructor. */
	UExportDataTableCommandlet();

public:

	//~ UCommandlet interface

	virtual int32 Main(const FString& Params) override;

	void SaveConfigToBin(FString& configStr, FString& outputPath);
	void LoadAndSave(ExportDataTableconfig& data, FString& outputPath);

	void Code(FString& sourceStr, int32 step = 1);
	void Decode(FString& sourceStr, int32 step = 1);

private:

	TArray<ExportDataTableconfig> configDatas;
};
