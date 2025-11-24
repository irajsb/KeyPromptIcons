// Copyright 2023 Iraj Mohtasham aurelion.net 

#include "KeyPromptIcons.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#endif 
#include "UMGSettings.h"

#define LOCTEXT_NAMESPACE "FKeyPromptIconsModule"

void FKeyPromptIconsModule::StartupModule()
{

#if WITH_EDITOR
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "KeyPromptIcons",
			LOCTEXT("KeyPromptIconsPage", "KeyPromptIcons"), LOCTEXT("KeyPromptIconsDesc", "Configure KeyPromptIcons"),
			GetMutableDefault<UKeyPromptSettings>());

	
		
	}
#endif
	
}

void FKeyPromptIconsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FKeyPromptIconsModule, KeyPromptIcons)