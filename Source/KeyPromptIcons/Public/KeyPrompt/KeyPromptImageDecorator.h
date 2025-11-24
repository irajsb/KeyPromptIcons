// Copyright 2023 Iraj Mohtasham aurelion.net 

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "KeyPromptImageDecorator.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable, BlueprintType)
struct KEYPROMPTICONS_API FTitanRichImageRow : public FRichImageRow
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Appearance")
	FKey Key;

	
};

UCLASS(HideCategories=Appearance,Blueprintable,BlueprintType)
class KEYPROMPTICONS_API UKeyPromptImageDecorator : public URichTextBlockImageDecorator
{
	GENERATED_BODY()
	virtual const FSlateBrush* FindImageBrush(FName TagOrId, bool bWarnIfMissing) override;
	UPROPERTY(EditAnywhere, meta = (RequiredAssetDataTags = "RowStructure=TitanRichImageRow"),Category="Setup")
	class UDataTable* PromptSet;

	
	
		
	
};
