// Copyright 2023 Iraj Mohtasham aurelion.net 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "UMGSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Engine)
class KEYPROMPTICONS_API UKeyPromptSettings : public UObject
{
	GENERATED_BODY()

	UKeyPromptSettings();
public:
	UPROPERTY( Config,EditAnywhere, Category = "Advanced")
	TArray<FSoftObjectPath> KeyPromptsPlatforms;
	
	
};
