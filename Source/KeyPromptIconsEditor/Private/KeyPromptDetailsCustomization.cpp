// Copyright 2023 Iraj Mohtasham aurelion.net 


#include "KeyPromptDetailsCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "KeyPrompt/KeyPrompt.h"
#include "UMGSettings.h"
#include "KeyPrompt/KeyPromptImageDecorator.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "KeyPromptCustomization"

class UUMGSettings;



TSharedRef<IDetailCustomization> KeyPromptDetailsCustomization::MakeInstance()
{
	return MakeShareable(new KeyPromptDetailsCustomization);
}

void KeyPromptDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	LayoutBuilder=&DetailBuilder;

	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);
	if(ObjectsBeingCustomized.Num()!=1)
	{
		//TODO show multiple objects
		return;
	}
	else
	{
		KeyPrompt=Cast<UKeyPrompt>(ObjectsBeingCustomized[0].Get());
	}
	
	const auto Settings=GetMutableDefault<UKeyPromptSettings>();
	PlatformProperty=DetailBuilder.GetProperty("CurrentPlatform");
	PromptProperty=	DetailBuilder.GetProperty("CurrentPrompt");
	for(auto Platform:Settings->KeyPromptsPlatforms)
	{
	SupportedDataTables.Add(MakeShareable(new FString(Platform.GetAssetName())));

		if(KeyPrompt->CurrentPlatform.IsEmpty())
		{
			UE_LOG(LogTemp,Log,TEXT("Current platform empty"))
		
			PlatformProperty->SetValue(*SupportedDataTables[0].Get());
			
			UObject * DT = Platform.TryLoad();
			const FString PromptName=Cast<UDataTable>(DT)->GetRowNames()[0].ToString();
			
			UE_LOG(LogTemp,Log,TEXT("Prompt set to %s by CustomizeDetails"),*PromptName)
			
			const auto Result=PromptProperty->SetValue(PromptName);
			if(Result==FPropertyAccess::Fail)
			{
				UE_LOG(LogTemp,Error,TEXT("CurrentPrompt set failed CustomizeDetails"));
			}
			
		}
	}
	
	GeneratePromptsOptions(false);

	ComboBox = SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&SupportedDataTables)
				.OnGenerateWidget(this, &KeyPromptDetailsCustomization::OnGeneratePlatformComboRow)
				.OnSelectionChanged(this, &KeyPromptDetailsCustomization::OnHandlePlatformSelection)
				[
					SNew(STextBlock)
						.Text(this, &KeyPromptDetailsCustomization::GetPlatformComboText)
						
				];
	//


	auto& Category=	DetailBuilder.EditCategory("Key",LOCTEXT("Key", "Key"));
	Category.SetSortOrder(0);
	///
	Category.AddCustomRow(FText::GetEmpty()).NameWidget[	SNew(STextBlock)
	.Text(LOCTEXT("Platform", "Platform"))].ValueWidget[
	ComboBox.ToSharedRef()
	];

	

	BuildSearchBox(Category);
	GridPanel = SNew(SUniformGridPanel);

	// Create a scroll box to make the panel scrollable
	TSharedPtr<SScrollBox> ScrollBox = SNew(SScrollBox)
										   .Orientation(Orient_Vertical)
										   .ScrollBarAlwaysVisible(true);

	ScrollBox->AddSlot()
		.Padding(5.0f)
			[GridPanel.ToSharedRef()];
	// Add a uniform grid panel
	// Add the scroll box to the category
	Category.AddCustomRow(FText::GetEmpty())
		.WholeRowContent()
		.VAlign(VAlign_Center)
			[SNew(SBox).MaxDesiredHeight(500)[ScrollBox.ToSharedRef()]];

	
	RebuildGridPanel();
	
}

ECheckBoxState KeyPromptDetailsCustomization::IsIconSelected(FString NewSelection) const
{
	return KeyPrompt->CurrentPrompt== NewSelection ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void KeyPromptDetailsCustomization::RebuildGridPanel()
{
	auto BuildFontButtons = [this](FSlateBrush* DisplayImage, FString DisplayName) -> TSharedRef<SWidget>
	{
		// Create a button with text child
		auto Font=FAppStyle::Get().GetFontStyle("SmallFont");
		return SNew(SCheckBox)
			.Style(FAppStyle::Get(), "DetailsView.SectionButton")
				[

					SNew(SVerticalBox) + SVerticalBox::Slot()[SNew(SImage).Image(DisplayImage)].VAlign(VAlign_Bottom).HAlign(HAlign_Center).FillHeight(0.6) + SVerticalBox::Slot()[SNew(STextBlock).Font(Font).Text(FText::FromString(DisplayName)).Justification(ETextJustify::Center).AutoWrapText(true).WrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping)].VAlign(VAlign_Center).HAlign(HAlign_Fill).FillHeight(0.4)]
			.Padding(FMargin(0))
			.IsChecked(this, &KeyPromptDetailsCustomization::IsIconSelected, DisplayName)
			.OnCheckStateChanged(this, &KeyPromptDetailsCustomization::OnIconSelectionChange, DisplayName);
	};

	// Load Data Table
	GridPanel->ClearChildren();
	TArray<FTitanRichImageRow *> Array;
	DataTable->GetAllRows("Details Panel", Array);
	auto Rows = DataTable->GetRowNames();
	auto Query = SearchBox.Get()->GetText().ToString();

	int FoundIndex = 0;
	for (int Index = 0; Index != Array.Num(); ++Index)
	{
		if (Query.IsEmpty() || Rows[Index].ToString().Contains(Query))
		{

			FTitanRichImageRow *CurrentItem = Array[Index];
			
			
			GridPanel->AddSlot(FoundIndex % 6, FoundIndex / 6)[

				SNew(SBox).HAlign(HAlign_Fill).VAlign(VAlign_Center).MinDesiredHeight(90).MaxDesiredHeight(90).MinDesiredWidth(90).MaxDesiredWidth(90)[BuildFontButtons(&CurrentItem->Brush, Rows[Index].ToString())

			]
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)];

			FoundIndex++;
		}
	}
}

void KeyPromptDetailsCustomization::BuildSearchBox(IDetailCategoryBuilder& Category)
{

	Category.AddCustomRow(FText::GetEmpty())
		.WholeRowContent()
			[SAssignNew(SearchBox, SSearchBox)
				 .OnTextChanged_Lambda([this](const FText &InSearchText)
									   { RebuildGridPanel(); })];
}

void KeyPromptDetailsCustomization::OnIconSelectionChange(ECheckBoxState State, FString NewSelection) const
{

	if(State==ECheckBoxState::Checked)
	{
		const FString PromptResult=NewSelection;
		const auto Result=PromptProperty->SetValue(PromptResult);
		
		
		
		if(Result==FPropertyAccess::Fail)
		{
			UE_LOG(LogTemp,Error,TEXT("CurrentPrompt set failed OnHandlePromptSelection "));
		}
		UE_LOG(LogTemp,Log,TEXT("Prompt set to %s by OnHandlePromptSelection"),*NewSelection)
	}
	
}

TSharedRef<SWidget> KeyPromptDetailsCustomization::OnGeneratePlatformComboRow(TSharedPtr<FString> InItem) const
{
	FText RowText = LOCTEXT("PlatformComboRow_Error", "Invalid");

	if(InItem.IsValid())
	{
		RowText = FText::FromString( *InItem.Get());
	}

	return SNew(STextBlock).Text(RowText);
}

void KeyPromptDetailsCustomization::OnHandlePlatformSelection(TSharedPtr<FString> InItem,
	ESelectInfo::Type InSelectInfo)
{

	
	GeneratePromptsOptions(true);
	PlatformProperty->SetValue(*InItem.Get());
	LayoutBuilder->ForceRefreshDetails();
	RebuildGridPanel();
	
	
}

FText KeyPromptDetailsCustomization::GetPlatformComboText() const
{
	return	FText::FromString( KeyPrompt->CurrentPlatform);
}






void KeyPromptDetailsCustomization::GeneratePromptsOptions(bool SetInitialPrompt)
{
	const auto Settings=GetMutableDefault<UKeyPromptSettings>();
	Prompts.Empty();
	if(KeyPrompt)
	{
		if(!KeyPrompt->CurrentPlatform.IsEmpty())
		{
			for(auto Platform :Settings->KeyPromptsPlatforms)
			{
				if(KeyPrompt->CurrentPlatform==Platform.GetAssetName())
				{
					UObject* DT=	Platform.TryLoad();
					DataTable= Cast<UDataTable>(DT);
					auto Rows=Cast<UDataTable>(DT)->GetRowNames();
					
					if(SetInitialPrompt)
					{
						const auto Result =PromptProperty->SetValue(Rows[0].ToString());
						if(Result==FPropertyAccess::Fail)
						{
							UE_LOG(LogTemp,Error,TEXT("CurrentPrompt set failed GeneratePromptsOptions"));
						}
					}
					for (auto Row: Rows)
					{
						Prompts.Add(MakeShareable(new FString(Row.ToString())));
					}
				}
			}
		}
	}
}
#undef LOCTEXT_NAMESPACE
