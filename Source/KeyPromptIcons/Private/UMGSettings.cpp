// Copyright 2023 Iraj Mohtasham aurelion.net 


#include "UMGSettings.h"

UKeyPromptSettings::UKeyPromptSettings()
{
	KeyPromptsPlatforms.AddUnique(FString("DataTable'/KeyPromptIcons/KeyPrompts/KeyboardAndMouse/Dark/DT_DarkPC.DT_DarkPC'"));
	KeyPromptsPlatforms.AddUnique(FString("DataTable'/KeyPromptIcons/KeyPrompts/KeyboardAndMouse/Light/DT_LightPC.DT_LightPC'"));
	KeyPromptsPlatforms.AddUnique(FString("DataTable'/KeyPromptIcons/KeyPrompts/Touch/DT_Touch.DT_Touch'"));
	
}
