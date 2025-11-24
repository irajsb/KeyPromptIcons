// Copyright 2023 Iraj Mohtasham aurelion.net 


#include "KeyPrompt/KeyPromptImageDecorator.h"

const FSlateBrush* UKeyPromptImageDecorator::FindImageBrush(FName TagOrId, bool bWarnIfMissing)
{
	const FString ContextString;
	const FRichImageRow* ImageRow =  PromptSet->FindRow<FTitanRichImageRow>(TagOrId, ContextString, bWarnIfMissing);
	if (ImageRow)
	{
		return &ImageRow->Brush;
	}
	return nullptr;
}

