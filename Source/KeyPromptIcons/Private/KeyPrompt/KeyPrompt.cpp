// Copyright 2023 Iraj Mohtasham aurelion.net 


#include "KeyPrompt/KeyPrompt.h"
#include "UMGSettings.h"
#include "KeyPrompt/KeyPromptImageDecorator.h"

#if WITH_EDITORONLY_DATA
FString UKeyPrompt::GetCurrentPrompt()
{
	return  CurrentPrompt;
}
#endif
#if WITH_EDITOR
void UKeyPrompt::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{

	Super::PostEditChangeProperty(PropertyChangedEvent);
	if(PropertyChangedEvent.GetPropertyName().ToString().Equals("CurrentPrompt"))
	{
		const auto Settings=GetMutableDefault<UKeyPromptSettings>();

		for(auto Platform :Settings->KeyPromptsPlatforms)
		{
			if(CurrentPlatform==Platform.GetAssetName())
			{
				UObject* DT=	Platform.TryLoad();
				const FName RowName=	FName(CurrentPrompt);
				const auto Result=Cast<UDataTable>(DT)->FindRow<FTitanRichImageRow>(RowName,"Updating prompt");
				if(Result)
				{
					SetBrush(Result->Brush);
				}
			}
		} 
	}
}
#endif
TSharedRef<SWidget> UKeyPrompt::RebuildWidget()
{
	return Super::RebuildWidget();
	
}



void UKeyPrompt::GetBrushForKey(UDataTable* DataTable, FKey InKey,FTitanRichImageRow& Output) const
{
	if(!DataTable)
	{
		return;
	}
	for (TMap<FName, uint8*>::TConstIterator RowMapIter(DataTable->GetRowMap().CreateConstIterator()); RowMapIter; ++RowMapIter)
	{
		const FTitanRichImageRow* Entry = reinterpret_cast<FTitanRichImageRow*>(RowMapIter.Value());

		if(Entry->Key==InKey)
		{
			Output=*Entry;
			return;
		}	
	}
	UE_LOG(LogTemp,Warning,TEXT("No key found in data table %s"),*DataTable->GetName())
}

void UKeyPrompt::GetKeyPromptBrush(const FTitanRichImageRow In,FSlateBrush& OutBrush,FVector2D DesiredSize)const
{
	OutBrush=In.Brush;
	OutBrush.ImageSize=DesiredSize;
}