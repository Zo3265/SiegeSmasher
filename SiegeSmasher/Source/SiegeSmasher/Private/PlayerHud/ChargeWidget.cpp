// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud/ChargeWidget.h"
#include "../MyMainCharacterTest.h"
#include "ImageUtils.h"
#include "Engine/Canvas.h"



void UChargeWidget::NativeConstruct() {

	Super::NativeConstruct();
	
	
	SceneCapture = Cast<ASceneCapture2D>( UGameplayStatics::GetActorOfClass(GetWorld(), ASceneCapture2D::StaticClass()));
	
	LeaderboardBorder = WidgetTree->FindWidget<UBorder>(FName(LeaderBoardBorderName));
	LeaderboardGrid = WidgetTree->FindWidget<UGridPanel>(FName(LeaderBoardGridPanelName));
	LeaderboardHeader = WidgetTree->FindWidget<UBorder>(FName(LeaderBoardHeaderName));
	MiniMapRef = WidgetTree->FindWidget<UImage>(FName(MiniMapName));

	if (!MiniMapRef || !SceneCapture ) {
		GLog->Log(FString::Printf(TEXT("MINIMAP NO SCENE CAPTURE IN LEVEL OR MINI MAP IMAGE IN PLAYER IMAGE ")));
		GLog->Log(FString::Printf(TEXT("MINIMAP NO SCENE CAPTURE IN LEVEL OR MINI MAP IMAGE IN PLAYER WIDGET  ")));

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("MINIMAP NOT FOUND IN PLAYER WIDGET OR SCENE CAPTURE 2D NOT IN SCENE ")));
	}
	else 
	{
	  
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("MINIMAP  FOUND IN PLAYER WIDGET")));

		UCanvasPanelSlot* MiniMapSlot = Cast<UCanvasPanelSlot>(MiniMapRef->Slot);
		MiniMapWidth = MiniMapSlot->GetSize().X; 
		MiniMapHeight = MiniMapSlot->GetSize().Y;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("MINIMAP  WIDTH %d"),MiniMapWidth));

		FCreateTexture2DParameters params = FCreateTexture2DParameters();
		
		UKismetRenderingLibrary::ReadRenderTarget(this, SceneCapture->GetCaptureComponent2D()->TextureTarget, MiniMapColBuffer,false);
		MiniMapSceneTexture = FImageUtils::CreateTexture2D(MiniMapWidth, MiniMapHeight, MiniMapColBuffer, this, FString("MiniMapSceneTex"), EObjectFlags::RF_Transient, params);

		UMaterial* parent = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/MiniMapMaterials/MiniMapSceneDisplay.MiniMapSceneDisplay'"));
		MiniMapDisplayMat = UMaterialInstanceDynamic::Create(parent, this, FName("SceneMapDisplayInstance"));
		  
		MiniMapDisplayMat->SetTextureParameterValue("LevelTex", MiniMapSceneTexture);
		MiniMapRef->SetBrushFromMaterial(MiniMapDisplayMat);

	} 
	
	if (LeaderboardGrid && LeaderboardHeader && LeaderboardBorder) {

		GLog->Log(FString::Printf(TEXT("Leaderboard border found")));
		
		GenerateLeaderBoard();
	}
		
	else {
		GLog->Log(FString::Printf(TEXT("NO LEADER BOARD border ")));

	}

	






}


// ui updates in unreal come after the main update loop(where all the mini map data is written) 
// so we know the mini map data will have been established, so for now we can call this within a tick event 
// within the player ui blueprint to tell the mini map manager that the ui update has been reached and that
// it can clear next frame, could have a more robust solution for the mini map to do this itself(counting number 
// of potential writes so that we know when to set the clear flag to true within the mini map ) but this 
// would require more coupling with the wave manager and the server object which is not required by 
// just using the fact ui updates after main game loop updates(where objects write to to the mini map manager)
void UChargeWidget::ClearMiniMap()
{			
		MiniMapManagerRef->ShouldClearNextFrame(true);
}


void UChargeWidget::GenerateLeaderBoard()
{
	LeaderBoardItems = {};

	


	// get the canavs slot of the leaderboard border that is created in the widget ui
	if (UCanvasPanelSlot* LeaderboardCanvasSlot = Cast<UCanvasPanelSlot>(LeaderboardGrid->Slot)) {
		// get the top left of the canavas slot of the leaderboard 
		FVector2D LeaderboardTopLeft = LeaderboardCanvasSlot->GetPosition();
		FVector2D LeaderboardSize = LeaderboardCanvasSlot->GetSize();
		for (int i = 0; i < MaxPlayerNum; i++) {


			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Itertaing max player num")));
		    // get a position based on the defined padding for each element that will be added to the leaderboard for each possible player
			FVector2D TextPosition = FVector2D(LeaderboardTopLeft.X, (LeaderboardTopLeft.Y + LeaderboardTextPadding * i) + LeaderboardTopPadding);
			FString PlayerTag = LeaderBoardTagName + FString::FromInt(i + 1);
			UTextBlock* Text = CreateText(PlayerTag);

			UScaleBox* TextScaleBox = CreateScaleBox(FString("Scale " + FString::FromInt(i)));
			LeaderboardGrid->GetParent()->AddChild(TextScaleBox);
			// get the canavas slot of the textscalebox after the parenting it to the top element within the widget tree
			UCanvasPanelSlot* TextScaleCanvasSlot = Cast<UCanvasPanelSlot>(TextScaleBox->Slot);
			// set the size to the defined scale box hight within the blueprint and adjust the size to be the leaderboardsize but with padding to the right 
			TextScaleCanvasSlot->SetSize(FVector2D(LeaderboardSize.X - LeaderboardScaleBoxRightPadding, LeaderboardScaleBoxHeight));
			// set anchors to be the same as the leaderboard border so that the text remains relative to the same part of the screen
			TextScaleCanvasSlot->SetAnchors(LeaderboardCanvasSlot->GetAnchors());
			TextScaleCanvasSlot->SetPosition(TextPosition);
			TextScaleBox->AddChild(Text);


			// set the visiblty of the text and the opacity 

			Text->SetVisibility(ESlateVisibility::Visible);

			Text->SetOpacity(0.0f);
			// add the text to the tracked leaderboard items
			LeaderBoardItems.Add(Text);

		

			
		}
		// hide every other element associated with the leaderboard 
		 LeaderboardBorder->SetRenderOpacity(0.0f); 
         LeaderboardHeader->SetRenderOpacity(0.0f); 
		 LeaderboardGrid->SetRenderOpacity(0.0f);
	}

}
// create a text box and add it to the widget tree
UTextBlock* UChargeWidget::CreateText(FString TextContent)
{
	UTextBlock* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), FName(TextContent));

	Text->SetFont(LeaderboardFont);
	Text->SetColorAndOpacity(LeaderboardTextColour);
	Text->SetText(FText::FromString(TextContent));
	return Text;
}

void UChargeWidget::DrawToMiniMapBuffer(UTextureRenderTarget2D* targetToDrawTo,UTexture2D* MiniMapIconTextureToUse)
{

	UCanvas* canvas;
	FVector2D canvasSize;
	FDrawToRenderTargetContext context;

	MiniMapDisplayMat->SetTextureParameterValue("IconsTexture", MiniMapIconTextureToUse);

	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(this, targetToDrawTo, canvas, canvasSize, context);


	canvas->K2_DrawMaterial(MiniMapDisplayMat, FVector2D(0.0), canvasSize, FVector2D(0.0), FVector2D(1.0));


	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(this, context);


}
	
// create a scale box and add it to the widget tree
UScaleBox* UChargeWidget::CreateScaleBox(FString Name)
{
	UScaleBox* ScaleBox = WidgetTree->ConstructWidget<UScaleBox>(UScaleBox::StaticClass(), FName(Name));

	ScaleBox->SetStretch(EStretch::ScaleToFit); 
	return ScaleBox;
}

void UChargeWidget::SetChargeAmount(float ChargeAmount)
{
	Charge = ChargeAmount;
}

float UChargeWidget::GetChargePercent()
{
	return Charge/100;
}

void UChargeWidget::SetHealthAmount(float HealthAmount)
{
	Health = HealthAmount;
}

float UChargeWidget::GetHealthAmount()
{
	return Health;
}

float UChargeWidget::GetHealthPercent()
{
	return Health/100;
}

void UChargeWidget::HideLeaderBoard(bool ShouldHide)
{
	// go through all elements on the leaderboard and set their opacity based on the past in boolean
	float NewOpacity = ((float)ShouldHide); 

	GLog->Log(FString::Printf(TEXT("Should hide %f"), NewOpacity));

	LeaderboardBorder->SetRenderOpacity(NewOpacity);
	LeaderboardHeader->SetRenderOpacity(NewOpacity); 
	LeaderboardGrid->SetRenderOpacity(NewOpacity);

	if (ServerobjectRef != nullptr) {
		int CurrentPlayerCount = ServerobjectRef->GetPlayerCurrentCount(); 

		GLog->Log((FString::Printf(TEXT("Server object player count %d"), CurrentPlayerCount)));

		for (int i = 0; i < CurrentPlayerCount; i++) {

			LeaderBoardItems[i]->SetOpacity(NewOpacity );
	    }
	}
	


}

void UChargeWidget::SetPoints(int NewPoints)
{
	PlayerPoints = NewPoints;

}

int UChargeWidget::GetPoints()
{
	return PlayerPoints;
}

void UChargeWidget::SetServerObjectRef(AServerObject* ServerObjectPtr)
{
	ServerobjectRef = ServerObjectPtr;
	
}

void UChargeWidget::AssignMiniMap(AMiniMapManager* MiniMapManagerPtr)
{
	 MiniMapManagerRef = MiniMapManagerPtr;
	 MiniMapManagerRef->SetMiniMapParams(MiniMapWidth, MiniMapHeight);
	
	 MiniMapDisplayMat->SetTextureParameterValue("IconsTexture", MiniMapManagerRef->GetMiniMapBuffer());
		  
	 
	


}



void UChargeWidget::UpdatePlayerLeaderBoardInfo(int Points, int Kills, int PlayerId)
{
	if (PlayerId >= 0 && PlayerId < LeaderBoardItems.Num()) {
		FString LeaderboardTxt = LeaderBoardTagName + FString::FromInt(PlayerId + 1) + " " + "Points:" + FString::FromInt(Points) + " Kills:" + FString::FromInt(Kills);

		LeaderBoardItems[PlayerId]->SetText(FText::FromString(LeaderboardTxt));
		LeaderBoardItems[PlayerId]->SetOpacity((LeaderboardBorder->GetRenderOpacity() > 0.0f));
		return;
	}

    GLog->Log(FString::Printf(TEXT("PLAYER ID WAS NULL WHEN TRYING TO UPDATE SLOT ON LEADERBOARD")));


	
}

void UChargeWidget::RefreshPlayerLeaderboardInfo()
{
	
	
	FPlayerLeaderBoardInfo info = FPlayerLeaderBoardInfo();

	// referesh a players leaderboard adding and updating any infomration that has changed since the last update 
	for (int i = 0; i < ServerobjectRef->GetPlayerCurrentCount(); i++) {


		info = ServerobjectRef->GetPlayerInfo(i);
        
		FString LeaderboardTxt = LeaderBoardTagName + FString::FromInt(i + 1) + " " + "Points:" + FString::FromInt(info.LeaderboardPlayerScore) + " Kills:" + FString::FromInt(info.LeaderboardPlayerKills);

		LeaderBoardItems[i]->SetText(FText::FromString(LeaderboardTxt)); 
	    
		LeaderBoardItems[i]->SetOpacity( ((float)(LeaderboardHeader->GetRenderOpacity() > 0.0f)));

	}


}



// used to hligh a specifc players tag on the leadboard using the defined highlight colour in the blueprint 
void UChargeWidget::HighlightPlayerTag(int PlayerIdForTag)
{
	if (PlayerIdForTag >= 0 && PlayerIdForTag < LeaderBoardItems.Num()) {
		LeaderBoardItems[PlayerIdForTag]->SetColorAndOpacity(LeaderboardHighlightColour);
		LeaderBoardItems[PlayerIdForTag]->SetOpacity(((float)(LeaderboardHeader->GetRenderOpacity() > 0.0f)));


	}



}

int UChargeWidget::GetThroneHealth()
{
	return ThroneHealth;
}

void UChargeWidget::SetThroneHealth(int NewHealth)
{
	ThroneHealth = NewHealth;
}

int UChargeWidget::GetPlayerWaveNumber()
{
	return DisplayedPlayerWaveNumber;
}


void UChargeWidget::SetPlayerWaveNumber(int WaveNumber) {

	DisplayedPlayerWaveNumber = WaveNumber;

}