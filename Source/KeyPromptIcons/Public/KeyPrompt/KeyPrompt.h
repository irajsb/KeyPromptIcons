// Copyright 2023 Iraj Mohtasham aurelion.net 

#pragma once

#include "CoreMinimal.h"
#include "KeyPromptImageDecorator.h"
#include "Components/Image.h"
#include "KeyPrompt.generated.h"

/**
 * Key icons that can be selected from a list of platforms and keys 
 */
UCLASS()
class KEYPROMPTICONS_API UKeyPrompt : public UImage 
{
	GENERATED_BODY()
	
#if WITH_EDITORONLY_DATA

public:


	
	FString GetCurrentPrompt();
	
	UPROPERTY(EditAnywhere,AdvancedDisplay,Category="KeyPrompt")
	FString CurrentPlatform;
	UPROPERTY(EditAnywhere,AdvancedDisplay,Category="KeyPrompt")
	FString CurrentPrompt;
	


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	

	
#endif

	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="KeyPrompt")
	void GetBrushForKey(UDataTable* DataTable, FKey InKey, FTitanRichImageRow& Output) const;
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="KeyPrompt")
	void GetKeyPromptBrush(FTitanRichImageRow In, FSlateBrush& OutBrush, FVector2D DesiredSize)const ;
};
