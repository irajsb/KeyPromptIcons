// Copyright 2023 Iraj Mohtasham aurelion.net 

#include "KeyPromptIconsEditor.h"

#include "ISettingsModule.h"
#include "KeyPromptDetailsCustomization.h"
#include "UMGSettings.h"

#define LOCTEXT_NAMESPACE "FKeyPromptIconsEditorModule"

void FKeyPromptIconsEditorModule::StartupModule()
{


	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("KeyPrompt",FOnGetDetailCustomizationInstance::CreateStatic(&KeyPromptDetailsCustomization::MakeInstance));

	
}

void FKeyPromptIconsEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FKeyPromptIconsEditorModule, KeyPromptIconsEditor)