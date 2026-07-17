// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/MCArrow.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h" 
#include "ServerObject/ServerObject.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerHud/ChargeWidget.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"
#include "../TowerPrePlacementObject/TowePrePlaceObjectHelper.h"
#include "Towers/TowerBase.h" 
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" 
#include "Throne.h"
#include "../MiniMapManager/MiniMapManager.h"
#include "MyMainCharacterTest.generated.h"

UCLASS()
class SIEGESMASHER_API AMainCharacterTest : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacterTest();
	void SetPlayerOwnerShip(AActor* ActorToOwn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Camera and Spring arm components
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* TPSCameraComponent;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	//Bools that handle animations 
	UPROPERTY(VisibleAnywhere, Category = "Input", Replicated);
	bool ArrowDrawn;

	UPROPERTY(VisibleAnywhere, Category = "Input", Replicated);
	bool ArrowFired;
	
	//flaot and bool for the Charging mechanic 
	UPROPERTY(Replicated);
	float MaxCharge;

	UPROPERTY(Replicated);
	float ChargeRate;

	UPROPERTY(Replicated);
	float CurrentCharge;

	UPROPERTY(Replicated);
	bool isCharging;

	UPROPERTY(Replicated);
	float ChargeFinal;

	UPROPERTY()
	bool CanShoot = true;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputMappingContext* DefaultContext; //The defult input mapping context. This will change depending on what context the player is in such as driving.

	//Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* JumpAction;

	

	//Move input action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* MoveAction;

	//Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* TowerPlacementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* SwitchTowerAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* ToggleTowerPlacementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* ToggleLeaderboardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	class UInputAction* RotateTower;


	//Calling for movement input
	void Move(const FInputActionValue& Value);

	//Calling for look input
	void Look(const FInputActionValue& Value);

	//calling for Jump input
	void Jumping();

	//function that handles shooting
	void Shoot();
	//sets bools for animations and starts the charging of the arrow
	void DrawBow();
	//same as draw bow but in reverse
	void StopAim();
	//increments the Current Charge variable
	void ChargeShot(float DeltaTime);
	// Place towers
	void PlaceTower();
	// allows player to toggle tower placement on and off
	void ToggleTowerPlacement();
	// swicth towers using number keys 
	void SwitchTowers();

	void RotateSelectedTower();

	void ToggleLeaderboard();
	void SetPlayerId(int Id);
	void UpdateLeaderboardInfo(int NewPlayerPoints, int NewPlayerKills, int PlayerIdToUpdate);
	void UpdateLeaderboard();
	void IncrementPlayerScore(int Increment);
	void DecrementPlayerScore(int Increment);
	UFUNCTION(Server,Reliable)
	void Server_IncrementPlayerScore(int increment);
	void Server_IncrementPlayerScore_Implementation(int increment);
	void IncrementPlayerKills();
	UFUNCTION(Server,Reliable)
	void Server_UpdatePlayerInfoKills();
	void Server_UpdatePlayerInfoKills_Implementation();

	void IncrementPlayerKills(int Increment);

	UFUNCTION(Server,Reliable)
	void Server_UpdatePlayerInfoKillsInc(int inc);
	void Server_UpdatePlayerInfoKillsInc_Implementation(int inc);

	UChargeWidget* GetPlayerWidget();

	//input for triggering the shooting action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ShootAction;
	//input for triggering the draw action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* DrawAction;
	//input that triggers stop aiming, which makes the player go back to their default animations
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* StopAimAction;

	//Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Replicated,  Category = "Projectile")
	TSubclassOf<class AMCArrow> ArrowClass;
	//Static mesh that serves as a spawning point for the arrows
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay");
	UStaticMeshComponent* BowPosition;
	//Reference to the widget that will be created, it has to be a subclass of the UserWidget
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Charge")
	TSubclassOf<class UUserWidget> PlayerHUD;
	//Holds the created widget
	UPROPERTY()
	class UChargeWidget* ChargeWidget;

	UPROPERTY(EditAnywhere,Category = "GameOver")
	TSubclassOf<UUserWidget> ServerGameOverWidgetToCreate;

	UPROPERTY(EditAnywhere, Category = "GameOver")
	TSubclassOf<UUserWidget> ClientGameOverWidgetToCreate;

	UPROPERTY()
	UUserWidget* ServerGameOverWidget;

	UPROPERTY()
	UUserWidget* ClientGameOverWidget;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowersTypesToSpawn");
	TArray<TSubclassOf<ATowerBase>> TowerTypesToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerPlacementObjects")
	TArray<TSubclassOf<ATowePrePlaceObjectHelper>> TowerPrePlacementObjectsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Placement distances");
	FVector PlayerPlacementDistances;
	
	


	//getters and seeters for the bools for the animation blueprint
	UFUNCTION(BlueprintCallable)
	bool GetArrowDrawn();

	UFUNCTION(BlueprintCallable)
	void SetArrowDrawn(bool isArrowDrawn);

	UFUNCTION(BlueprintCallable)
	bool GetArrowFired();

	UFUNCTION(BlueprintCallable)
	void SetArrowFired(bool isArrowDrawn);

	void setHealth(float HealthStore);

	float getHealth();

	UFUNCTION(NetMulticast,Reliable) 
	void Multicast_HighlightPlayerId(int PlayerServerId); 
	void Multicast_HighlightPlayerId_Implementation(int PlayerServerId);

	UFUNCTION()
	float GetCurrentCharge();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SpawnProjectile(FRotator CamRotation, FRotator BowRot);
	void Server_SpawnProjectile_Implementation(FRotator CamRotation, FRotator BowRot);
	bool Server_SpawnProjectile_Validate(FRotator CamRotation, FRotator BowRot);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ChargeShot(float DeltaTime);
	void Server_ChargeShot_Implementation(float DeltaTime);
	bool Server_ChargeShot_Validate(float DeltaTime);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpdateCharge(float ClientCharge);
	void Server_UpdateCharge_Implementation(float ClientCharge);
	bool Server_UpdateCharge_Validate(float ClientCharge);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_DrawBow();
	void Server_DrawBow_Implementation();
	bool Server_DrawBow_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StopAim();
	void Server_StopAim_Implementation();
	bool Server_StopAim_Validate();

	UFUNCTION(Server, Reliable)
	void Server_SetPlayerOwnerShip(AActor* ActorToOwn);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetPlayerOwnerShip(AActor* ActorToOwn);

	void TowerPlacementHandle();

	UFUNCTION(Server,Reliable)
	void Server_HandleTowerPlacement(FVector CamForward,FVector CamPosition); 

	void Server_HandleTowerPlacement_Implementation(FVector CamForward, FVector CamPosition);
	
	


	UFUNCTION(Server,Reliable) 
	void Server_SetPlaceTower(bool PlaceTower); 
	void Server_SetPlaceTower_Implementation(bool PlaceTower);

	UFUNCTION(Server, Unreliable) 
	void Server_PushSelected(FTransform ClientSelectedTransform,FVector SelectRayStart,FVector SelectRayEnd,FVector SelectedRayDir);
	void Server_PushSelected_Implementation(FTransform ClientSelectedTransform,FVector SelectRayStart,FVector SelectRayEnd,FVector SelectedRayDir);

	
	UFUNCTION(Server, Reliable)
	void Server_IncrementTowerPlacementRot();
	void Server_IncrementTowerPlacementRot_Implementation();

	void SpawnSelected();
	UFUNCTION(Server, Reliable)
	void Server_SpawnSelected(bool PlacingTower, bool ToggleTower);
	void Server_SpawnSelected_Implementation(bool PlacingTower, bool ToggleTower);


	UFUNCTION(Server,Reliable)
	void Server_RefreshLeaderboard();
	void Server_RefreshLeaderboard_Implementation(); 

	UFUNCTION(NetMulticast,Reliable) 
	void Multicast_RefreshLeaderboard(); 
	void Multicast_RefreshLeaderboard_Implementation();

	void RefreshLeaderBoard();

	UFUNCTION(Server,Reliable) 
	void Server_SwitchTower(int SelectedIndex, bool ToggleTower); 
	
	void Server_SwitchTower_Implementation(int SelectedIndex,bool ToggleTower);
	
	UFUNCTION(Server,Reliable) 
	void Server_HideSelected(); 
	void Server_HideSelected_Implementation();

	UFUNCTION(Server, Reliable)
	void Server_DisplaySelected();
	void Server_DisplaySelected_Implementation();

	

	UFUNCTION(Server,Reliable) 
	void Server_AssignPlayerId(int Id);
	void Server_AssignPlayerId_Implementation(int Id);

	

	UFUNCTION(Server, Reliable)
	void Server_IncrementLoggedPlayerCount(); 
	void Server_IncrementLoggedPlayerCount_Implementation();

	
	int GetScore(); 
	int GetKills();



	UFUNCTION(Server,Reliable)
	void Server_ToggleTowers(bool ToggleTower);
	void Server_ToggleTowers_Implementation(bool ToggleTower);

	UFUNCTION(Server, Reliable)
	void Server_SetHealth(float HealthStore);

	void Server_SetHealth_Implementation(float HealthStore);

	UFUNCTION()
	void PlayImpactSound();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_PlaySound(USoundBase* Sound);
	void Multi_PlaySound_Implementation(USoundBase* Sound);
	bool Multi_PlaySound_Validate(USoundBase* Sound);

	UFUNCTION()
	void PlayerDeath();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdateChargeBar();

	void Multicast_UpdateChargeBar_Implementation();

	UPROPERTY()
	FVector PlayerRespawnPoint;

	//Online Lobby 
	UFUNCTION(BlueprintCallable)
	void CallCreateLobby();

	UFUNCTION(BlueprintCallable)
	void CallClientTravel(const FString& Address);  

	void AdjustLeaderBoardValues(int LeaderboardPlayerPoints, int LeaderboardPlayerKils);
	void UpdateLeaderBoardInfo();

	int GetPlayerId();
	void HighlightPlayerTagOnLeaderboard();
	void HighlightPlayerTagOnLeaderboard(int LeaderBoardPlayerId);


	UFUNCTION()
	void SetBaseHealth(int NewHealth);

	UFUNCTION()
	void GameOver();
protected:
	UFUNCTION()
	void UpdatePlayerScoreUi();
	UPROPERTY(Replicated)
    int PlayerKills = 0;
	UPROPERTY(ReplicatedUsing = UpdatePlayerScoreUi);
	int PlayerPoints = 0; 

	UFUNCTION(NetMulticast, Reliable)
	void MultiCast_UpdateLeaderBoardInfo(int NewPlayerPoints, int NewPlayerKills, int TargetPlayerId); 

	void MultiCast_UpdateLeaderBoardInfo_Implementation(int NewPlayerPoints, int NewPlayerKills, int TargetPlayerId);

	UFUNCTION()
	void UpdateHealthWidget();

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* FiringSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* DrawingSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* ArrowImpact;
	
	
	

	UPROPERTY(Replicated);
	int PlayerId = 0; 

	
	AServerObject* ServerObjectRef = nullptr;
	AMiniMapManager* miniMapManagertRef = nullptr;

	AThrone* ThroneRef = nullptr;

	void SetUpPlayerId();
	
	UFUNCTION(NetMulticast,Reliable) 
	void Multicast_SetLeaderBoardTxt(int NewPlayerPoint, int NewPlayerKills, int LeaderBoardPlayerId); 
	void Multicast_SetLeaderBoardTxt_Implementation(int NewPlayerPoints, int NewPlayerKills, int LeaderBoardPlayerId);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points");
	int StartingPoints = 1000;
private:
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = nullptr;
		TArray<ATowePrePlaceObjectHelper*> TowerPrePlacementObjects; 
		
		ATowePrePlaceObjectHelper* Selected = nullptr; 
		UWorld* World = nullptr;
		APlayerController* AssignedPlayerController = nullptr;
		FActorSpawnParameters TowerSpawnParameters;
		
		UPROPERTY(Replicated);
		int SelectedTowerIndex = -1;

		UPROPERTY(ReplicatedUsing = UpdateHealthWidget)
		float Health = 100.0f;
		UPROPERTY(Replicated);
		bool IsPlacingTower = false;

		bool TogglePlacingTowers = false;
		bool ToggleShowLeaderboard = false;
		FCollisionQueryParams TraceParams;
		void DisplaySelected();
		void HideSelected();
		void ClientSwitchTower(); 
		
		void HandleTowerPlacement();
		void InitialiseTowers(); 

		void ClientTowerPlacment();
		void WriteToMiniMap();
		double MiniMapSectionRadius = 0.03;
		UPROPERTY();
		UMaterialInstanceDynamic* MiniMapMat;

};
