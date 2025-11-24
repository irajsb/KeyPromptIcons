// Copyright 2023 Iraj Mohtasham aurelion.net 

#pragma once

#include "Modules/ModuleManager.h"

class FKeyPromptIconsEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
