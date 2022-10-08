// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Commandlets/Commandlet.h"

#include "ImportStringTableCommandlet.generated.h"


UCLASS()
class UImportStringTableCommandlet
	: public UCommandlet
{
	GENERATED_BODY()

public:

	/** Default constructor. */
	UImportStringTableCommandlet();

public:

	//~ UCommandlet interface

	virtual int32 Main(const FString& Params) override;

protected:
	virtual void InitCommandLine(const FString& Params);
	FString From;
	FString To;
	TArray<FAssetData> FindAssetList;
};
