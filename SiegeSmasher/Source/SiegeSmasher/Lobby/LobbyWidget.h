// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Blueprint/WidgetTree.h"  
#include "Net/UnrealNetwork.h"

#include "Components/Image.h"  
#include "Components/CanvasPanel.h" 
#include "Components/GridSlot.h"
#include "Components/Overlay.h"
#include "Components/CanvasPanelSlot.h" 
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/TextBlock.h"
#include "Components/OverlaySlot.h"
#include "Engine/Texture2D.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FLevelSelectSection
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image");
	UTexture2D *Texture ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelPathNameAndSelectionName");
	FString LevelName; 
	


};


struct FLevelSelectionContainerState
{
	
	UCanvasPanel* LevelSelectSection = nullptr;
	float targetScrollY = 0.0f;
	
	FLevelSelectionContainerState() {}
	FLevelSelectionContainerState(UCanvasPanel* section, float targetScrollValueY) : LevelSelectSection(section), targetScrollY(targetScrollValueY) {}
	 


};




UCLASS()
class SIEGESMASHER_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
 
 public:
	 void NativeConstruct();
	 void NativeTick(const FGeometry& geom, float deltaTime);
	 FReply NativeOnMouseButtonUp(const FGeometry& geom, const FPointerEvent& event);
     FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	 FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	 UFUNCTION(BlueprintCallable)
	 FString GetTravelCommand() const;
	 

 protected:
	

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSelectGridName");
	 FName LevelSelectGridName;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelImageBorderName");
	 FName LevelImageBorderName;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSelectGridItems");
	 TArray<FLevelSelectSection> LevelSelectSectionData;

	

	 UPROPERTY(BlueprintReadOnly);
	 FString SelectedLevelCommand;




	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSelectionImageHeight")
	 float LevelSelectionGridHeight; 

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSelectUIPadding");
	 float LevelTextLeftPadding;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSelectUIPadding");
	 float LevelTextTopPadding;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSelectUIPadding");
	 float LevelImageSpacing;


	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelTextCustomisation");
	 FSlateFontInfo LevelTextFontInfo; 

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSelectInput"); 
	 float scrollStep = 10.0f;


	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSelectInput");
	 float scrollInterpSpeedMin = 3000.0f;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSelectInput");
	 float scrollInterpSpeedMax = 7000.0f;

 private:
	 TArray<FLevelSelectionContainerState> LevelSelectionContainerState;
	 
	 void UpdateLevelSelect(float deltaTime);

	 bool ScrollBoundaryCheck();
	 UCanvasPanel* LevelSelectPanel = nullptr;
	 UCanvasPanelSlot* LevelSelectionMainPanel = nullptr;
	 UCanvasPanelSlot* LevelSelectHighlightBorderSlot = nullptr;
	 UBorder* LevelSelectHighlightBorder = nullptr;
	 FString HoveredCommand;
	 float CurrentLevelSelectInterpSpeed = 0.0f; 
	 float ScrollSnapBackDir = 0.0f;
	 bool HasScrollSnapBack = false;
	 bool HasHoveredLevel = false; 
	 bool MouseDown = false;
	 float ScrollSnapBack();
};
