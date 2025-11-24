// Copyright 2023 Iraj Mohtasham aurelion.net 

#pragma once

#include "CoreMinimal.h"
#include "DetailWidgetRow.h"
#include "IDetailCustomization.h"
#include "Widgets/Layout/SUniformGridPanel.h"

/**
 * 
 */

class UKeyPrompt;


class KEYPROMPTICONSEDITOR_API KeyPromptDetailsCustomization: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	/** IDetailCustomization interface */
	virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;


private:



	ECheckBoxState IsIconSelected(FString NewSelection) const;
	void RebuildGridPanel();


	void BuildSearchBox(IDetailCategoryBuilder &Category);

	void OnIconSelectionChange(ECheckBoxState State, FString NewSelection) const;
	UKeyPrompt* KeyPrompt=nullptr;
	TSharedRef<SWidget> OnGeneratePlatformComboRow(TSharedPtr<FString> InItem) const;
	void OnHandlePlatformSelection(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectInfo);
	FText GetPlatformComboText() const;


	

	void GeneratePromptsOptions(bool SetInitialPrompt);
	TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;
	
	TArray<TSharedPtr<FString>> SupportedDataTables;
	TArray<TSharedPtr<FString>> Prompts;
	TSharedPtr<IPropertyHandle> PromptProperty;
	TSharedPtr<IPropertyHandle> PlatformProperty;
	UDataTable *DataTable=nullptr;
	TSharedPtr<SUniformGridPanel> GridPanel;
	TSharedPtr<SSearchBox> SearchBox;
	IDetailLayoutBuilder *LayoutBuilder=nullptr;
};
