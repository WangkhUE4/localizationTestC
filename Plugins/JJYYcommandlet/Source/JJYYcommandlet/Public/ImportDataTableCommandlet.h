// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Commandlets/Commandlet.h"
#include "ImportDataTableCommandlet.generated.h"


UCLASS()
class UImportDataTableCommandlet
	: public UCommandlet
{
	GENERATED_BODY()

public:

	/** Default constructor. */
	UImportDataTableCommandlet();

public:

	//~ UCommandlet interface

	virtual int32 Main(const FString& Params) override;

protected:
	virtual void InitCommandLine(const FString& Params);

	FString PreProcessFileName;
	FString ImportDataFileName;


};
