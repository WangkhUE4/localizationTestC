// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "Logging/LogMacros.h"


/** Declares a log category for this module. */
DECLARE_LOG_CATEGORY_EXTERN(logJJYYcommandlet, Log, All);

class FJJYYcommandletModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
