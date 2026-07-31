// Fill out your copyright notice in the Description page of Project Settings.


#include "../Lobby/LobbyWidget.h"



void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	LevelSelectPanel = WidgetTree->FindWidget<UCanvasPanel>(LevelSelectGridName);
	LevelSelectHighlightBorder = WidgetTree->FindWidget<UBorder>(LevelImageBorderName);

    
	if (LevelSelectPanel && LevelSelectHighlightBorder)
	{ 
	   
	    LevelSelectionMainPanel = Cast<UCanvasPanelSlot>(LevelSelectPanel->Slot);
		LevelSelectHighlightBorderSlot = Cast<UCanvasPanelSlot>(LevelSelectHighlightBorder->Slot);
		//LevelSelectHighlightBorder->SetVisibility(ESlateVisibility::Hidden);
		LevelSelectHighlightBorder->SetRenderScale(FVector2D(0.0f));
		GLog->Log("canavas slot for level selection grid was not null");

		for (int i = 0; i < LevelSelectSectionData.Num(); i++)
		{
			FLevelSelectSection& Data = LevelSelectSectionData[i];
			UCanvasPanel* LevelSelectionSection = WidgetTree->ConstructWidget<UCanvasPanel>();  
			LevelSelectPanel->AddChild(LevelSelectionSection);
		    

			UCanvasPanelSlot* LevelSelectSectionPanel = Cast<UCanvasPanelSlot>(LevelSelectionSection->Slot);
			LevelSelectSectionPanel->SetSize(FVector2D(LevelSelectionMainPanel->GetSize().X,LevelSelectionGridHeight));
			LevelSelectSectionPanel->SetAnchors(LevelSelectionMainPanel->GetAnchors());
			LevelSelectSectionPanel->SetPosition(FVector2D(0.0f, (LevelSelectionGridHeight * i + LevelImageSpacing * i )));

		    UImage* LevelImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		    LevelSelectionSection->AddChild(LevelImage);
		    UCanvasPanelSlot* ImagePanelSlot = Cast<UCanvasPanelSlot>(LevelImage->Slot);
		    LevelImage->SetBrushFromTexture(Data.Texture);
		    ImagePanelSlot->SetSize(FVector2D(LevelSelectionMainPanel->GetSize().X, LevelSelectionGridHeight));
		    ImagePanelSlot->SetPosition(FVector2D(0.0f));
		    
		    UTextBlock* Leveltext = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		    LevelSelectionSection->AddChild(Leveltext);
		    Leveltext->SetFont(LevelTextFontInfo);
		    Leveltext->SetText(FText::FromString(Data.LevelName));
		    
		    UCanvasPanelSlot* LevelTextSlot = Cast<UCanvasPanelSlot>(Leveltext->Slot);
		    LevelTextSlot->SetPosition(FVector2D(LevelTextLeftPadding, LevelTextTopPadding));
		    
		    LevelSelectionContainerState.Emplace(LevelSelectionSection, LevelSelectSectionPanel->GetPosition().Y);



		}
    
	  }
		

	
	
	





}


FReply ULobbyWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,FString::Printf(TEXT("scroll delta ")));

	if(LevelSelectPanel->IsHovered())
	{
		float scrollDelta = InMouseEvent.GetWheelDelta(); 

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,FString::Printf(TEXT("scroll delta %f"), scrollDelta));

		CurrentLevelSelectInterpSpeed = (scrollInterpSpeedMin + (scrollInterpSpeedMax - scrollInterpSpeedMin) * abs(scrollDelta)) * (scrollDelta != 0.0f);

		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,FString::Printf(TEXT("scroll speed %f"), CurrentLevelSelectInterpSpeed));
		for (FLevelSelectionContainerState& LevelSelectSection : LevelSelectionContainerState)
		{
			UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(LevelSelectSection.LevelSelectSection->Slot);
			FVector2D position = slot->GetPosition();
			
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("scroll step %f %f"), scrollDelta,scrollStep ));

			float nextTarget = position.Y + (scrollDelta)*scrollStep;
			
		    LevelSelectSection.targetScrollY = position.Y + (scrollDelta) * scrollStep;

			
			
			

			
		}
	
	 
		if(HasScrollSnapBack && !ScrollBoundaryCheck())
		{ 
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("no scroll snap back %d"), (int)HasScrollSnapBack));

			HasScrollSnapBack = false;

		}
		
	}

	
	


	return FReply::Handled();

}

FString ULobbyWidget::GetTravelCommand() const
{
	return FString("ServerTravel /Game/"+SelectedLevelCommand+"?listen");
}




void ULobbyWidget::NativeTick(const FGeometry& geom, float deltaTime)
{
	Super::NativeTick(geom, deltaTime);
	UpdateLevelSelect(deltaTime);

}

void ULobbyWidget::UpdateLevelSelect(float deltaTime)
{
	UCanvasPanelSlot* SelectionContainer = Cast<UCanvasPanelSlot>(LevelSelectPanel->Slot);
	float ContainerTopY = SelectionContainer->GetPosition().Y;
	float ContainerBottomY = ContainerTopY + SelectionContainer->GetSize().Y;
	float ScrollBoundarySnapBack = ScrollSnapBack();
	
	FVector2D LevelSelectBorderScale = FVector2D(0.0f);
	HasHoveredLevel = false;
	for (int i = 0; i < LevelSelectionContainerState.Num(); i++)
	{
		UCanvasPanel* LevelSelection = LevelSelectionContainerState[i].LevelSelectSection;
		
		UCanvasPanelSlot* LevelSelectionSlot = Cast<UCanvasPanelSlot>(LevelSelection->Slot);
		FVector2D mousePos =  GetCachedGeometry().AbsoluteToLocal(FSlateApplication::Get().GetCursorPos());
		FVector2D sectionLeft = LevelSelectionMainPanel->GetPosition() + LevelSelectionSlot->GetPosition();
		FVector2D sectionRight = sectionLeft + LevelSelectionSlot->GetSize();

		
		if (mousePos.X >= sectionLeft.X && mousePos.X <= sectionRight.X
			&& mousePos.Y >= sectionLeft.Y && mousePos.Y <= sectionRight.Y)
		{

			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("element is hovered %d "),i));
			LevelSelectHighlightBorderSlot->SetPosition(FVector2D(LevelSelectHighlightBorderSlot->GetPosition().X, LevelSelectionSlot->GetPosition().Y));
			LevelSelectBorderScale = FVector2D(1.0f);
			HasHoveredLevel = true;
			HoveredCommand = LevelSelectSectionData[i].LevelName;

		}
		
		float SelectionPositionY = ContainerTopY + LevelSelectionSlot->GetPosition().Y;
	    float SelectionPositionExtentsY = SelectionPositionY + LevelSelectionGridHeight;	
		bool disable = SelectionPositionY > ContainerBottomY || SelectionPositionExtentsY < ContainerTopY;
		LevelSelection->SetRenderOpacity(!disable);
	   
		float TargetY = LevelSelectionContainerState[i].targetScrollY;
		float Yposition = LevelSelectionSlot->GetPosition().Y;
		float NextY = FMath::FInterpTo(Yposition, TargetY, deltaTime, CurrentLevelSelectInterpSpeed);
		if(ScrollBoundarySnapBack == 0.0f && !HasScrollSnapBack )
		{
			LevelSelectionSlot->SetPosition(FVector2D(LevelSelectionSlot->GetPosition().X, NextY));
			continue;

		}
		float YSnap = Yposition + ScrollBoundarySnapBack; 
		HasScrollSnapBack = true;
		LevelSelectionSlot->SetPosition(FVector2D(LevelSelectionSlot->GetPosition().X, YSnap));
	
	}
	LevelSelectHighlightBorder->SetRenderScale(LevelSelectBorderScale);
}





bool ULobbyWidget::ScrollBoundaryCheck()
{

	FVector2D TopElementPos = Cast<UCanvasPanelSlot>(LevelSelectionContainerState[0].LevelSelectSection->Slot)->GetPosition();
	FVector2D BottomElementPos = Cast<UCanvasPanelSlot>(LevelSelectionContainerState[LevelSelectionContainerState.Num() - 1].LevelSelectSection->Slot)->GetPosition();
	GLog->Log(FString::Printf(TEXT("top element pos y %f"), (float)TopElementPos.Y));

	bool NoScrollUpSnapBack = (LevelSelectionContainerState[0].targetScrollY >= TopElementPos.Y && TopElementPos.Y >= 0.0f);

	float bottomElementPosExtent = BottomElementPos.Y + LevelSelectionGridHeight;
	bool NoScrollDownSnapBack = (LevelSelectionContainerState[LevelSelectionContainerState.Num() - 1].targetScrollY <= BottomElementPos.Y &&
		 bottomElementPosExtent <= LevelSelectionMainPanel->GetSize().Y);


	return NoScrollUpSnapBack || NoScrollDownSnapBack;

}


float ULobbyWidget::ScrollSnapBack()
{

	FVector2D TopElementPos =  Cast<UCanvasPanelSlot>(LevelSelectionContainerState[0].LevelSelectSection->Slot)->GetPosition();
	FVector2D BottomElementPos = Cast<UCanvasPanelSlot>(LevelSelectionContainerState[LevelSelectionContainerState.Num() - 1].LevelSelectSection->Slot)->GetPosition() ;
	GLog->Log(FString::Printf(TEXT("top element pos y %f"),(float)TopElementPos.Y));

	float NoScrollUpSnapBack = (LevelSelectionContainerState[0].targetScrollY >= TopElementPos.Y && TopElementPos.Y >= 0.0f) * (0.0f - TopElementPos.Y) ;
	float bottomElementPosExtent = BottomElementPos.Y + LevelSelectionGridHeight;

	float NoScrollDownSnapBack = (LevelSelectionContainerState[LevelSelectionContainerState.Num() - 1].targetScrollY <= BottomElementPos.Y && 
		                 bottomElementPosExtent <= LevelSelectionMainPanel->GetSize().Y)  * (LevelSelectionMainPanel->GetSize().Y - bottomElementPosExtent);



	return NoScrollUpSnapBack + NoScrollDownSnapBack;
}






FReply ULobbyWidget::NativeOnMouseButtonDown(const FGeometry& geom, const FPointerEvent& event)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("mouse button down has hovered level is %d"),(int)HasHoveredLevel));

	if (event.IsMouseButtonDown(EKeys::LeftMouseButton) && HasHoveredLevel) 
	{
		SelectedLevelCommand = HoveredCommand;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("mouse button down selected level command is now %s"), *SelectedLevelCommand));

	}


	return FReply::Handled();

}


FReply ULobbyWidget::NativeOnMouseButtonUp(const FGeometry& geom, const FPointerEvent& event)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("mouse button up")));

	
	
			 
	

	return FReply::Handled();
}

void Server_SetTravelCommand(const FString& TravelCommand)
{


}