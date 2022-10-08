// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Commandlets/Commandlet.h"
#include "Runtime/AssetRegistry/Public/AssetData.h"
#include "CheckResourceCommandlet.generated.h"


UCLASS()
class UCheckResourceCommandlet
	: public UCommandlet
{
	GENERATED_BODY()

public:

	/** Default constructor. */
	UCheckResourceCommandlet();

public:

	//~ UCommandlet interface

	virtual int32 Main(const FString& Params) override;

protected:
	virtual void InitCommandLine(const FString& Params);
	FString path;
	TArray<FString> paths;
	TArray<FAssetData> FindAssetList;
};
