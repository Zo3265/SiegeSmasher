// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMainCharacterTest.h"

// Fill out your copyright notice in the Description page of Project Settings.
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"

// Sets default values
AMainCharacterTest::AMainCharacterTest()
{
	TowerSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//Test comment for commit
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//Spring Arm Component is attached to Mesh
	SpringArmComponent->SetupAttachment(CastChecked<USceneComponent,
		UCapsuleComponent>(GetCapsuleComponent()));
	// Create a Third person camera component.
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	//Attach CameraComponent as a child of Spring Arm
	TPSCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	//Allows the tick function to play
	PrimaryActorTick.bCanEverTick = true;

	//Creates the static mesh and assigns it to the socket 
	BowPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowPosition"));
	BowPosition->SetupAttachment(AMainCharacterTest::GetMesh(), TEXT("BowPosition"));
	//Default values for the charge mechanic
	isCharging = false;
	MaxCharge = 100.0f;
	CurrentCharge = 0.0f;
	ChargeRate = 50.0f;
}

// Called when the game starts or when spawned
void AMainCharacterTest::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();

	
	if (SpringArmComponent != nullptr)
	{
		//Set Location and Rotation
		SpringArmComponent->SetRelativeLocation(FVector(0.0f, 80.0f, 100.0f));
		SpringArmComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		// Set How far away from character
		SpringArmComponent->TargetArmLength = 250.0f;
		// Set camera lag behaviour
		SpringArmComponent->bEnableCameraLag = true;
		SpringArmComponent->CameraLagSpeed = 20.0f;
	}
	if (TPSCameraComponent != nullptr)
	{
		// Camera pawn rotation must be enabled to allow player to move camera
		TPSCameraComponent->bUsePawnControlRotation = true;
	}

	//Adding the input mapping context to the main character
	/*A reference to the player controller class is being cast to the controller that is currently controlling this actor*/
	AssignedPlayerController = Cast<APlayerController>(Controller);

	if (AssignedPlayerController)
	{
		InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(AssignedPlayerController->GetLocalPlayer());
		
		if (InputSubsystem)
		{
			//Adding our defaultcontext to the input subsystem that each local player has.
			//The zero refers to its priority. With zero being the lowest priority.
			//If we had multiple we would assign them differnt priority with asscending giving them higher priority.
			InputSubsystem->AddMappingContext(DefaultContext, 0);
		}
	}
	//Reference for The Server Object and The Base that are placed in the level
	ServerObjectRef = Cast<AServerObject>(UGameplayStatics::GetActorOfClass(World,AServerObject::StaticClass()));
	miniMapManagertRef = Cast<AMiniMapManager>(UGameplayStatics::GetActorOfClass(World, AMiniMapManager::StaticClass()));
	ThroneRef = Cast<AThrone>(UGameplayStatics::GetActorOfClass(World, AThrone::StaticClass()));
	UMaterial* parent = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/MiniMapMaterials/PlayerMiniMapMat.PlayerMiniMapMat'"));

	MiniMapMat = UMaterialInstanceDynamic::Create(parent, this, FName("PlayerMiniMapMat"));

	//checks if the reference to the player hud is not empty

	if (PlayerHUD != nullptr) 
	{


		//IsLocallyControlled checks if the pawn is controlled by a local controller and not cross network 
		if (IsLocallyControlled()) 
		{
			//Gives the throne a reference to this player
			ThroneRef->SetPlayerRef(this);

			//creates the widget of the ChargeWidget class in the current world
			ChargeWidget = CreateWidget<UChargeWidget>(GetWorld(), PlayerHUD);
			//if the widget was created successfully, add it to viewport

			//checks if the widgets are not null to avoid crashes due to null reference
			if (ChargeWidget != nullptr && ServerObjectRef != nullptr && miniMapManagertRef != nullptr)
			{
				//Charge widget is the players UI, it gets added to the viewport on begin play and sets the health bar to the correct amount
				ChargeWidget->AddToViewport();
				ChargeWidget->SetHealthAmount(Health);
				
				//Gives the charge widget reference to the server object and server object the reference to this player
				ChargeWidget->SetServerObjectRef(ServerObjectRef);
				ServerObjectRef->SetPlayerStateToHandle(this);
				
				ChargeWidget->AssignMiniMap(miniMapManagertRef);

				//sets the base health to the correct value at begin play
				ChargeWidget->SetThroneHealth(ThroneRef->ThroneHealth);

				//Givrs the server object a reference to the Host of the multiplayer session
				if (HasAuthority()) {
					ServerObjectRef->SetHost(this);
				
					HighlightPlayerTagOnLeaderboard();



				}


			}

			
		}
	}
	//creates the Game Over widgets that will be added to the viewport when the player looses
	if(ServerGameOverWidgetToCreate != nullptr && ClientGameOverWidgetToCreate !=nullptr)
	{
		if (IsLocallyControlled()) 
		{
			ServerGameOverWidget = CreateWidget<UUserWidget>(GetWorld(), ServerGameOverWidgetToCreate);
			ClientGameOverWidget = CreateWidget<UUserWidget>(GetWorld(), ClientGameOverWidgetToCreate);
		}
	}
	


	InitialiseTowers();

	TraceParams = FCollisionQueryParams();
	TraceParams.AddIgnoredActor(this);

	PlayerRespawnPoint = GetActorLocation();


	SetUpPlayerId();

	PlayerPoints = StartingPoints;


	UpdatePlayerScoreUi();
		
	

	//RefreshLeaderBoard();
	if (IsLocallyControlled()) 
	{
		AssignedPlayerController->bShowMouseCursor = false;
	}

}

// Called every frame
void AMainCharacterTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChargeShot(DeltaTime);
	//if Charge widget is not empty, update the charge amount in the widget
	if (ChargeWidget != nullptr)
	{
		ChargeWidget->SetChargeAmount(CurrentCharge);


	}
	
	WriteToMiniMap();

	TowerPlacementHandle();

}

// Called to bind functionality to input
void AMainCharacterTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//Setting up the actual bindings to the keys now.
	//We check if the EnhancedInputComponenet has been casted to the PlayerInputComponent. If the check returns false the program will crash.
	//Because the player wont be able to do any actions.
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacterTest::Jumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacterTest::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacterTest::Look);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AMainCharacterTest::Shoot);

		EnhancedInputComponent->BindAction(DrawAction, ETriggerEvent::Triggered, this, &AMainCharacterTest::DrawBow);

		EnhancedInputComponent->BindAction(StopAimAction, ETriggerEvent::Triggered, this, &AMainCharacterTest::StopAim);

		EnhancedInputComponent->BindAction(TowerPlacementAction, ETriggerEvent::Started, this, &AMainCharacterTest::PlaceTower);

		EnhancedInputComponent->BindAction(SwitchTowerAction, ETriggerEvent::Started, this, &AMainCharacterTest::SwitchTowers);
		
		EnhancedInputComponent->BindAction(ToggleTowerPlacementAction, ETriggerEvent::Triggered, this, &AMainCharacterTest::ToggleTowerPlacement);
		
		EnhancedInputComponent->BindAction(ToggleLeaderboardAction, ETriggerEvent::Triggered, this, &AMainCharacterTest::ToggleLeaderboard); 
		
		EnhancedInputComponent->BindAction(RotateTower, ETriggerEvent::Triggered, this, &AMainCharacterTest::RotateSelectedTower);

		
	}
}

void AMainCharacterTest::Move(const FInputActionValue& Value)
{
	//Input is a Vector2d
	FVector2D MovementVector = Value.Get<FVector2D>();

	//This is if the user is using a controller
	if (Controller != nullptr)
	{
		//Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Get the forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		//Get the right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMainCharacterTest::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//Add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMainCharacterTest::Jumping()
{
	Jump();
}

void AMainCharacterTest::Shoot()
{
	//if statement checks if the player is not currently placing a tower
	if (CanShoot == true && CurrentCharge != 0.0f || !IsPlacingTower && CurrentCharge != 0.0f)
	{



		//Attempt to shoot a projectile.
		if (ArrowClass)
		{
			// Get the camera transform.
			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);
			FRotator BowRotation = CameraRotation;
			//gets the world the player is in
			//UWorld* World = GetWorld();
			if (World)
			{//spawn parameters of the arrow
				if (!HasAuthority())
				{
					//on client 
					Server_UpdateCharge(CurrentCharge);
					//Server_SpawnProjectile(CameraRotation, BowRotation);
					Server_SpawnProjectile(CameraRotation, BowRotation);
					CurrentCharge = 0;
				}

				else
				{
					//on Server
					if (FiringSound != nullptr)
					{
						UGameplayStatics::PlaySoundAtLocation(this, FiringSound, GetActorLocation());
					}
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = GetInstigator();
					//creates an actor of the Arrow class in the world, passes in the class, position to spawm, rotation and the parameters
					AMCArrow* Arrow = World->SpawnActor<AMCArrow>(ArrowClass, BowPosition->GetComponentLocation(), CameraRotation, SpawnParams);


					//if arrow has been succesfully created
					if (Arrow)
					{
						Arrow->SetPlayerRef(this);
						//changes the Bow rotation to be changed into a vector so that it shows a direction
						FVector LaunchDirection = BowRotation.Vector();
						//calls the fire in direction function from the arrow which makes it fly into the direction the player is rotated in, also takes charge to scale arrow speed
						Arrow->FireInDirection(LaunchDirection, CurrentCharge);
						//sets the bools for animations and turns off charging and resets the charge
						SetArrowDrawn(false);
						SetArrowFired(true);
						isCharging = false;
						//UE_LOG(LogTemp, Warning, TEXT("Function called on the server The Charge: %f Percent"), CurrentCharge);
						CurrentCharge = 0;

					}
				}
			}
		}
	}
}
//Sets all those variables to be replicated across the server and the clients
void AMainCharacterTest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainCharacterTest, ArrowDrawn);
	DOREPLIFETIME(AMainCharacterTest, ArrowFired);
	DOREPLIFETIME(AMainCharacterTest, MaxCharge);
	DOREPLIFETIME(AMainCharacterTest, ChargeRate);

	DOREPLIFETIME(AMainCharacterTest, SelectedTowerIndex);
	DOREPLIFETIME(AMainCharacterTest, IsPlacingTower);
	DOREPLIFETIME(AMainCharacterTest, isCharging);
	DOREPLIFETIME(AMainCharacterTest, ArrowClass);
	DOREPLIFETIME(AMainCharacterTest, ChargeFinal);  

	DOREPLIFETIME(AMainCharacterTest, Health);

	DOREPLIFETIME(AMainCharacterTest, PlayerPoints); 
	DOREPLIFETIME(AMainCharacterTest, PlayerKills); 
	DOREPLIFETIME(AMainCharacterTest, PlayerId);
	
}
//Getters and Setters
bool AMainCharacterTest::GetArrowDrawn()
{
	return ArrowDrawn;
}

void AMainCharacterTest::SetArrowDrawn(bool isArrowDrawn)
{
	ArrowDrawn = isArrowDrawn;
}

bool AMainCharacterTest::GetArrowFired()
{
	return ArrowFired;
}

void AMainCharacterTest::SetArrowFired(bool wasArrowShot)
{
	ArrowFired = wasArrowShot;
}

float AMainCharacterTest::GetCurrentCharge()
{
	return CurrentCharge;
}
//This function will execute on the Server, and since the arrow is being set to replicate it will spawn on the clients as well
void AMainCharacterTest::Server_SpawnProjectile_Implementation(FRotator CamRotation, FRotator BowRot)
{
	//multi cast from the sever plays on every client
	Multi_PlaySound(FiringSound);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	AMCArrow* Arrow = GetWorld()->SpawnActor<AMCArrow>(ArrowClass, BowPosition->GetComponentLocation(), CamRotation, SpawnParams);
	//if arrow has been succesfully created
	if (Arrow)
	{

		Arrow->SetPlayerRef(this);
		//changes the Bow rotation to be changed into a vector so that it shows a direction
		FVector LaunchDirection = BowRot.Vector();
		//calls the fire in direction function from the arrow which makes it fly into the direction the player is rotated in, also takes charge to scale arrow speed
		Arrow->FireInDirection(LaunchDirection, ChargeFinal);
		//sets the bools for animations and turns off charging and resets the charge
		SetArrowDrawn(false);
		SetArrowFired(true);
		isCharging = false;
		//UE_LOG(LogTemp, Warning, TEXT("Server Charge: %f Percent"), ChargeFinal);
		CurrentCharge = 0;
	}
}

bool AMainCharacterTest::Server_SpawnProjectile_Validate(FRotator CamRotation, FRotator BowRot)
{
	return true;
}
//charges the arrow on the server so that its charge value is corrent and therefore has the same damage and velocity as the client arrow
void AMainCharacterTest::Server_ChargeShot_Implementation(float DeltaTime)
{
	if (isCharging == true)
	{
		CurrentCharge += ChargeRate * DeltaTime;
		CurrentCharge = FMath::Clamp(CurrentCharge, 0.0f, MaxCharge);
	}
}

bool AMainCharacterTest::Server_ChargeShot_Validate(float DeltaTime)
{
	return true;
}


void AMainCharacterTest::Multicast_UpdateChargeBar_Implementation()
{
	if (ChargeWidget != nullptr)
	{
		CurrentCharge = 0.0f;
		ChargeWidget->SetChargeAmount(CurrentCharge);

	}
}


void AMainCharacterTest::Server_UpdateCharge_Implementation(float ClientCharge)
{
	ChargeFinal = ClientCharge;
	//UE_LOG(LogTemp, Warning, TEXT("Server Charge: %f Percent"), ChargeFinal);
}

bool AMainCharacterTest::Server_UpdateCharge_Validate(float ClientCharge)
{
	return true;
}
//This will be called on the sever to set animation bools 
void AMainCharacterTest::Server_DrawBow_Implementation()
{
	Multi_PlaySound(DrawingSound);
	SetArrowFired(false);
	SetArrowDrawn(true);
	//allows the charge value to increase
	isCharging = true;
}

bool AMainCharacterTest::Server_DrawBow_Validate()
{
	return true;
}
//same but for when the player stops aiming
void AMainCharacterTest::Server_StopAim_Implementation()
{
	SetArrowDrawn(false);
	SetArrowFired(true);
	isCharging = false;

	CurrentCharge = 0.0f;
	Multicast_UpdateChargeBar();
	//resets the charge value as the player either shot their arrow or is no longer drawing their bow
	CurrentCharge = 0.0f;
	if (ChargeWidget != nullptr)
	{
		ChargeWidget->SetChargeAmount(CurrentCharge);
	}
}

bool AMainCharacterTest::Server_StopAim_Validate()
{
	return true;
}

//Sets stuff for animation
void AMainCharacterTest::DrawBow()
{

	if (CanShoot == true || !IsPlacingTower)
	{


		//either calls the server function if currently on the client or just sets the booleans and plays the sound if on the server
		if (!HasAuthority())
		{
			//Client
			Server_DrawBow();

		}
		else
		{
			if (DrawingSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, DrawingSound, GetActorLocation());

			}
			//Server
			SetArrowFired(false);
			SetArrowDrawn(true);
			isCharging = true;
		}
	}
}
//same but for when the player is no longer aiming their bow
void AMainCharacterTest::StopAim()
{
	if (!HasAuthority()) 
	{
		//Client
		Server_StopAim();
	}

	else 
	{
		//Server
		SetArrowDrawn(false);
		SetArrowFired(true);
		isCharging = false;

		CurrentCharge = 0.0f;
		if (ChargeWidget != nullptr)
		{
			ChargeWidget->SetChargeAmount(CurrentCharge);
		}
	}
}
//increases the charge by delta time so the rate doesn't change based on player fps
void AMainCharacterTest::ChargeShot(float DeltaTime)
{
	if (isCharging == true) 
	{
		CurrentCharge += ChargeRate * DeltaTime;
		CurrentCharge = FMath::Clamp(CurrentCharge, 0.0f, MaxCharge);
	}
}
//multi casts the sound so it plays on everyones machine
void AMainCharacterTest::Multi_PlaySound_Implementation(USoundBase* Sound)
{
	if (Sound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
	}
}

bool AMainCharacterTest::Multi_PlaySound_Validate(USoundBase* Sound)
{
	return true;
}

//resets player location and takes away a 100 points as penalty
void AMainCharacterTest::PlayerDeath()
{
	SetActorLocation(PlayerRespawnPoint);
	DecrementPlayerScore(100);
	//UpdateLeaderBoardInfo();
	
	Health = 100.0f;

	if (ChargeWidget != nullptr) {

		UpdateHealthWidget();
	}
}

void AMainCharacterTest::Server_SetPlayerOwnerShip_Implementation(AActor* ActorToOwn)
{
	Multicast_SetPlayerOwnerShip(ActorToOwn);
}

void AMainCharacterTest::SetPlayerOwnerShip(AActor* ActorToOwn)
{

	if (!HasAuthority()) 
	{
		//Client
		Server_SetPlayerOwnerShip(ActorToOwn);
	}
	else 
	{
		//Server
		Multicast_SetPlayerOwnerShip(ActorToOwn);
	}

}

void AMainCharacterTest::Multicast_SetPlayerOwnerShip_Implementation(AActor* ActorToOwn)
{
	ActorToOwn->SetOwner(Controller);
}


void AMainCharacterTest::PlaceTower()
{
	SpawnSelected();
}

void AMainCharacterTest::ToggleTowerPlacement()
{
	TogglePlacingTowers = !TogglePlacingTowers;
	CanShoot = !CanShoot ;
	
	if (!HasAuthority()) {

		Server_ToggleTowers(TogglePlacingTowers);

	}
	else { 
		if (Selected != nullptr && !TogglePlacingTowers) {
			HideSelected();
		}
	}

}
	




// display the selected tower for the player when they are looking at a placing surface 
void AMainCharacterTest::DisplaySelected()
{
	if (HasAuthority()) {
		Selected->SetActorHiddenInGame(false);
		Selected->SetActorEnableCollision(true);
	}

}
// hide the current selected tower when the player toggles placing towers or when they are not hitting a placing surface 
void AMainCharacterTest::HideSelected()
{
	
	Selected->SetActorHiddenInGame(true);
	Selected->SetActorEnableCollision(false);
	Selected->SetActorTickEnabled(false);
}

void AMainCharacterTest::ClientSwitchTower()
{

	// here we use the adanced inout system to check which key the player pressed when switching to a tower 
	// and access the correct slot in the array used for selecting towers since the keys used to select towers are
	// in the same number 
	int index = 0;
	TArray<FKey> InputKeysToSwitchTower = InputSubsystem->QueryKeysMappedToAction(SwitchTowerAction);
	for (int i = 0; i < InputKeysToSwitchTower.Num(); i++) {

		if (i < TowerPrePlacementObjects.Num() &&
			AssignedPlayerController->WasInputKeyJustPressed(InputKeysToSwitchTower[i])) {

			index = i;
			break;
		}
	}

	

	// switch the index we stopped at when the client pressed a key on the server so the switch is displayed for all players
	Server_SwitchTower(index,TogglePlacingTowers);



}

void AMainCharacterTest::HandleTowerPlacement()
{
	// if we have toggled placing a tower and the tower we selected isnt nuull
	if (TogglePlacingTowers && Selected != nullptr) {

		// get the forward vector of the camera as that is the direction the player is looking
		FVector PlayerCameForward = TPSCameraComponent->GetForwardVector();

		FHitResult PlacementSurfaceResult = FHitResult();

		FVector start = TPSCameraComponent->GetComponentLocation() + PlayerCameForward;

		FVector end = start + PlayerCameForward * PlayerPlacementDistances;
		IsPlacingTower = false;
		// if the ray cast from the camera hits a placing surface 
		if (World->LineTraceSingleByChannel(PlacementSurfaceResult, start, end, PlacingSurface, TraceParams))
		{ 

			// display the selected tower for players 
			DisplaySelected();
			// get the collider of the surface we hit 
			UPrimitiveComponent* HitComponent = PlacementSurfaceResult.GetComponent();

			FVector SurfaceOrigin = HitComponent->GetComponentLocation();
			FTransform SurfaceTransform = HitComponent->GetComponentToWorld();
			FVector SurfaceLocalExtents = HitComponent->GetLocalBounds().GetBox().GetExtent() * SurfaceTransform.GetScale3D();
			FVector CamPos = TPSCameraComponent->GetComponentLocation();

		    // we are placing a tower if the placement can be resolved for the surface and if the surface is correct for the tower 
			IsPlacingTower = Selected->ResolvePlacement(SurfaceLocalExtents, SurfaceOrigin, PlacementSurfaceResult.ImpactPoint, PlayerCameForward, CamPos, SurfaceTransform);


			return;
		} 
		// other wise if ray doesnt hit hide the tower the player has selected 
		HideSelected();
	}
}

void AMainCharacterTest::InitialiseTowers()
{

	ATowePrePlaceObjectHelper* currentInstance = nullptr;
	UWorld* world = GetWorld();
	FTransform SpawnTransForm = FTransform();
	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GLog->Log(FString::Printf(TEXT("towers types to spawn count:%d"), TowerTypesToSpawn.Num()));

	// spawn all fo the tower plavement object helpers that will be used to determine if the player can place a tower
	for (TSubclassOf<ATowePrePlaceObjectHelper>& towerType : TowerPrePlacementObjectsToSpawn) {

		currentInstance = world->SpawnActor<ATowePrePlaceObjectHelper>(towerType, SpawnTransForm, SpawnParameters);
		TowerPrePlacementObjects.Add(currentInstance);
		currentInstance->SetActorHiddenInGame(true);
		currentInstance->SetActorEnableCollision(false);
		currentInstance->DisableTick();


	}

}

void AMainCharacterTest::ClientTowerPlacment()
{
	// used to place towers on the client if toggling placing towers is true and selectd is not null
	if (TogglePlacingTowers && Selected != nullptr) {
		
		FVector PlayerCamForward = TPSCameraComponent->GetForwardVector();

		FHitResult PlacementSurfaceResult = FHitResult();

		FVector start = TPSCameraComponent->GetComponentLocation() + PlayerCamForward;

		FVector end = start + PlayerCamForward * PlayerPlacementDistances;
		

		// we cast a ray to see if we hit a placing surface first on the client and then validate that ray cast on the server 
		if (World->LineTraceSingleByChannel(PlacementSurfaceResult, start, end, PlacingSurface, TraceParams))
		{

			//  display the selected on the server initially
			Server_DisplaySelected();

			// reslove the selected towers placement on the server 
			Server_PushSelected(Selected->GetActorTransform(),start,end,PlayerCamForward);

			return;
		}
		// hide the selected tower on the server if we dont get a hit on the placing ray
		Server_HideSelected();
	}




}

void AMainCharacterTest::CallCreateLobby()
{
	UWorld* MultiWorld = GetWorld();
	{
		MultiWorld->ServerTravel("/Game/Lobby?listen");
	}
}

void AMainCharacterTest::CallClientTravel(const FString& Address)
{
	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}






void AMainCharacterTest::UpdatePlayerScoreUi()
{
	

	if (ChargeWidget != nullptr) {
		ChargeWidget->SetPoints(PlayerPoints);
	}
	
}


void AMainCharacterTest::MultiCast_UpdateLeaderBoardInfo_Implementation(int NewPlayerPoints, int NewPlayerKills, int TargetPlayerId)
{

	if (ServerObjectRef != nullptr) {
		ServerObjectRef->UpdateStoredLeaderBoardInfo(PlayerPoints, PlayerKills, PlayerId);
		if (UChargeWidget* PlayerWidget = ServerObjectRef->GetLocalPlayer()->GetPlayerWidget()) {

			PlayerWidget->UpdatePlayerLeaderBoardInfo(NewPlayerPoints, NewPlayerKills, PlayerId);


		}
	}
	

}

void AMainCharacterTest::UpdateLeaderboardInfo(int NewPlayerPoints, int NewPlayerKills, int PlayerIdToUpdate)
{

	if (ChargeWidget != nullptr) {

	   ChargeWidget->UpdatePlayerLeaderBoardInfo(NewPlayerPoints, NewPlayerKills, PlayerIdToUpdate);


	}

}

void AMainCharacterTest::UpdateLeaderboard()
{

	if (HasAuthority() && ServerObjectRef != nullptr) {


		ServerObjectRef->UpdateStoredLeaderBoardInfo(PlayerPoints, PlayerKills, PlayerId);


	}

}



void AMainCharacterTest::UpdateLeaderBoardInfo()
{
	if (HasAuthority()) {

		MultiCast_UpdateLeaderBoardInfo(PlayerPoints, PlayerKills, PlayerId);

		

	}


}

void AMainCharacterTest::UpdateHealthWidget()
{
	if (ChargeWidget != nullptr) 
	{

		ChargeWidget->SetHealthAmount(Health);
	}
}
void AMainCharacterTest::HighlightPlayerTagOnLeaderboard()
{

	if (ChargeWidget != nullptr) {
		ChargeWidget->HighlightPlayerTag(PlayerId);
	}





}
void AMainCharacterTest::HighlightPlayerTagOnLeaderboard(int LeaderBoardPlayerId)
{
	if (ChargeWidget != nullptr) {
		ChargeWidget->HighlightPlayerTag(LeaderBoardPlayerId);
	}

}
void AMainCharacterTest::SetUpPlayerId()
{

	if (HasAuthority() && ServerObjectRef != nullptr) {
		PlayerId = ServerObjectRef->GetPlayerCurrentCount();
		ServerObjectRef->IncrementPlayerCount();

	}
	

}

int AMainCharacterTest::GetPlayerId()
{
	return PlayerId;
}



void AMainCharacterTest::Multicast_SetLeaderBoardTxt_Implementation(int NewPlayerPoints, int NewPlayerKills, int LeaderboardPlayerId)
{
	if (ChargeWidget != nullptr) {

		//ChargeWidget->UpdatePlayerLeaderBoardInfo(NewPlayerPoints, NewPlayerKills, LeaderboardPlayerId);



	}

}
//updates the Text that represents the Base's health in the UI
void AMainCharacterTest::SetBaseHealth(int NewHealth)
{
	if (ChargeWidget != nullptr) 
	{
		ChargeWidget->SetThroneHealth(NewHealth);
	}
}

void AMainCharacterTest::GameOver()
{
	//Pauses the game to avoid crashes
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	//checks if this is the person that acts as a server and if the player character is locally controlled as the widgets are only created for locally controlled player
	if (HasAuthority() && IsLocallyControlled()) 
	{
		//Shows the cursor and adds the game over widget that can restart the game to the viewport
		AssignedPlayerController->bShowMouseCursor = true;
		ServerGameOverWidget->AddToViewport();
	}

	else if (IsLocallyControlled()) 
	{
		//shows the cursor and adds the game over widget that can only quit to the viewport
		AssignedPlayerController->bShowMouseCursor = true;
		ClientGameOverWidget->AddToViewport();
	}
}
//set health function is called when an enemy damages the player 
void AMainCharacterTest::setHealth(float HealthStore)
{
	//Checks if its on the server or the client
	if (HasAuthority()) 
	{
		Health = HealthStore;
		if (ChargeWidget != nullptr)
		{
			ChargeWidget->SetHealthAmount(Health);
		}

		if (Health <= 0)
		{
			PlayerDeath();
		}

	}
	else 
	{
		Server_SetHealth(HealthStore);
	}
}
//same as above just fires on the server
void AMainCharacterTest::Server_SetHealth_Implementation(float HealthStore)
{
	Health = HealthStore;

	if (Health <= 0)
	{
		PlayerDeath();

	}

}
//plays a sound when the arrow impacts something
void AMainCharacterTest::PlayImpactSound()
{
	if (ArrowImpact != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ArrowImpact, GetActorLocation());
	}
}
//getter
float AMainCharacterTest::getHealth()
{
	return Health;
}

void AMainCharacterTest::Multicast_HighlightPlayerId_Implementation(int PlayerServerId)
{

	HighlightPlayerTagOnLeaderboard(PlayerServerId);
}



void AMainCharacterTest::WriteToMiniMap() 
{

	miniMapManagertRef->WriteToMiniMap(GetActorLocation(), GetActorRotation().Yaw ,MiniMapSectionRadius,MiniMapMat);



}




void AMainCharacterTest::SwitchTowers()
{

	TArray<FKey> InputKeysToSwitchTower = InputSubsystem->QueryKeysMappedToAction(SwitchTowerAction);
	for (int i = 0; i < InputKeysToSwitchTower.Num(); i++) {

		if (i < TowerPrePlacementObjects.Num() &&
			AssignedPlayerController->WasInputKeyJustPressed(InputKeysToSwitchTower[i])) {

			if (Selected != nullptr) {
				Selected->SetPlayerRotationAngle(0.0);
				HideSelected();
			}

			SelectedTowerIndex = i;
			Selected = TowerPrePlacementObjects[SelectedTowerIndex];
			if (TogglePlacingTowers) {
				DisplaySelected();
			}
		
			break;

		}
		}
	
	if(!HasAuthority()) { 
		ClientSwitchTower();
	}
	
}

void AMainCharacterTest::RotateSelectedTower()
{
	

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Rotate Tower Called")));

	if (!HasAuthority() ) {

		Server_IncrementTowerPlacementRot();
		return;
	}
	
	if (Selected != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Rotate Tower Called Server")));

		Selected->IncrementPlayerRotAngle();
	}
	
}

void AMainCharacterTest::ToggleLeaderboard()
{
	if (ChargeWidget != nullptr) {
		ToggleShowLeaderboard = !ToggleShowLeaderboard;
		ChargeWidget->HideLeaderBoard(ToggleShowLeaderboard);

	}




}




void AMainCharacterTest::TowerPlacementHandle()
{
	if (!HasAuthority() ) {
		
		ClientTowerPlacment();
	
		

	}
	else if(IsLocallyControlled()) {

		HandleTowerPlacement();

	}
	



}

void AMainCharacterTest::Server_HandleTowerPlacement_Implementation(FVector CamFoward, FVector CamPosition)
{
	// if the server has aselected tower
	if (Selected != nullptr) {
		
		FVector PlayerCamForward = CamFoward;

		FHitResult PlacementSurfaceResult = FHitResult();

		FVector start = CamPosition + PlayerCamForward;

		FVector end = start + PlayerCamForward * PlayerPlacementDistances;

		// cast aray form the cmaera and see if it can place the selected tower 
		if (World->LineTraceSingleByChannel(PlacementSurfaceResult, start, end, PlacingSurface, TraceParams))
		{
			
			// get the collider  of the object the ray hit 
			UPrimitiveComponent* HitComponent = PlacementSurfaceResult.GetComponent();
			
			FVector SurfaceOrigin = HitComponent->GetComponentLocation();
			FTransform SurfaceTransform = HitComponent->GetComponentToWorld();
			FVector SurfaceLocalExtents = HitComponent->GetLocalBounds().GetBox().GetExtent() * SurfaceTransform.GetScale3D();

			// set if the player is placing the tower on the server to ensure it is synced across the clients
		    Server_SetPlaceTower(  Selected->ResolvePlacement(SurfaceLocalExtents, SurfaceOrigin, PlacementSurfaceResult.ImpactPoint, PlayerCamForward, CamPosition, SurfaceTransform));

			return;
		}
		// other wise set placing tower on the server to false 
		Server_SetPlaceTower(false);

	}

}



void AMainCharacterTest::Server_SetPlaceTower_Implementation(bool PlaceTower)
{
	IsPlacingTower = PlaceTower;
}




void AMainCharacterTest::Server_IncrementTowerPlacementRot_Implementation()
{

	if (Selected != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Rotate Tower Called Client")));

		Selected->IncrementPlayerRotAngle();

	}


}

void AMainCharacterTest::SpawnSelected()
{
	// if the player has authoirty and they are locally controlled 
	if (HasAuthority() && IsLocallyControlled()) {
		if (TogglePlacingTowers 
			&& IsPlacingTower 
			&& Selected->GetCanPlaceTower() 
			&& PlayerPoints >= Selected->GetTowerCost()) 
		{
			// get the selected tower and spawn specifc type of the tower 
			ATowerBase* TowerRef = World->SpawnActor<ATowerBase>(TowerTypesToSpawn[SelectedTowerIndex], Selected->GetTransform(), TowerSpawnParameters);
			if (TowerRef) {
				
				TowerRef->SetOwner(Controller); 
				//set the player ref for this tower
				TowerRef->SetPlayerRef(this);
				TowerRef->HandleAppliedPlayerRotation(Selected->GetPlayerRot());

				// decrement the players score on the server after placing the tower
				DecrementPlayerScore(Selected->GetTowerCost());
				// update the players leaderboard info and cast to client
				//UpdateLeaderBoardInfo();


			}
		}
	}
	else {
		
		Server_SpawnSelected(IsPlacingTower,TogglePlacingTowers);
	}

}
void AMainCharacterTest::Server_PushSelected_Implementation(FTransform ClientSelectedTransform, FVector SelectRayStart, FVector SelectRayEnd,FVector SelectedRayDir)
{
	// if selected is no null meaning that the client has a selcted tower
	if (Selected != nullptr) {
		FHitResult result = FHitResult(); 
		// cast ray on server to validate raycast form client 
		if (World->LineTraceSingleByChannel(result, SelectRayStart, SelectRayEnd, PlacingSurface)) {

			DrawDebugLine(World, SelectRayStart, SelectRayEnd, FColor::Magenta);
			UPrimitiveComponent* HitComponent = result.GetComponent();

			FVector SurfaceOrigin = HitComponent->GetComponentLocation();
			FTransform SurfaceTransform = HitComponent->GetComponentToWorld();
			FVector SurfaceLocalExtents = HitComponent->GetLocalBounds().GetBox().GetExtent() * SurfaceTransform.GetScale3D();
			DrawDebugSphere(World, result.ImpactPoint, 15.0f, 8, FColor::Green);
			// set is placing tower on the server 
			IsPlacingTower = Selected->ResolvePlacement(SurfaceLocalExtents, SurfaceOrigin, result.ImpactPoint, SelectedRayDir, SelectRayStart, SurfaceTransform);

			return;
		}
		// hide the selected on the server if the ray on the client didnt actaully hit on object it can place on on  sever 
		HideSelected();
		


	}

}

void AMainCharacterTest::Server_SpawnSelected_Implementation(bool PlacingTower,bool ToggleTower)
{
    // spawn selected if the player is able to place the tower on the server 	
	if (ToggleTower && IsPlacingTower && 
		Selected->GetCanPlaceTower() && 
		PlayerPoints >= Selected->GetTowerCost() ) 
	{
		ATowerBase* TowerRef = World->SpawnActor<ATowerBase>(TowerTypesToSpawn[SelectedTowerIndex], Selected->GetTransform(), TowerSpawnParameters);
		if (TowerRef) {
			// set tower player ref on server
			TowerRef->SetPlayerRef(this);
			// set the applied player rotation and handle any adjustments needed based on it 
			TowerRef->HandleAppliedPlayerRotation(Selected->GetPlayerRot());
			// decrement player score indivual 
			DecrementPlayerScore(Selected->GetTowerCost()); 
			// update players score across all clients 
			//UpdateLeaderBoardInfo();
		}
	}
	
}

void AMainCharacterTest::Server_RefreshLeaderboard_Implementation()
{
	Multicast_RefreshLeaderboard();


}
// // refresh the leadboard for all players associated with this server object with the player 
void AMainCharacterTest::Multicast_RefreshLeaderboard_Implementation()
{

	if (ChargeWidget != nullptr && ServerObjectRef != nullptr) {

		ChargeWidget->RefreshPlayerLeaderboardInfo();


	}


}

void AMainCharacterTest::RefreshLeaderBoard()
{
	// if we have authority on this player character then we can multicast to update this players leadboard info on all clients and this player on the server
	if (HasAuthority() ) {
		
		Multicast_RefreshLeaderboard();
		
	
		
	}
	else {
		// otherwise we need to call the multicast on the server for the leadberoard info to be broadcasted across all client 
		Server_RefreshLeaderboard();

	}
}	
	




// switch the index of the tower the client has selected on the server 
void AMainCharacterTest::Server_SwitchTower_Implementation(int NewSelectedIndex, bool ToggleTower)
{
	 
	if (Selected != nullptr) {
		Selected->SetPlayerRotationAngle(0.0);
		HideSelected();
	}
	SelectedTowerIndex = NewSelectedIndex;
	Selected = TowerPrePlacementObjects[SelectedTowerIndex];
	if (ToggleTower) {
		DisplaySelected();
	}

}

void AMainCharacterTest::Server_HideSelected_Implementation()
{

	HideSelected();



}

void AMainCharacterTest::Server_DisplaySelected_Implementation()
{
	DisplaySelected();


}

void AMainCharacterTest::Server_AssignPlayerId_Implementation(int Id)
{

	PlayerId = Id;


}





// increment the logged player count of the server object assigned to this player 
void AMainCharacterTest::Server_IncrementLoggedPlayerCount_Implementation()
{
	if ( HasAuthority() && ServerObjectRef != nullptr) {
		ServerObjectRef->IncrementPlayerCount();  

		PlayerId = ServerObjectRef->GetCurrentPlayerId();

	}
	

}

int AMainCharacterTest::GetScore()
{
	return PlayerPoints;
}

int AMainCharacterTest::GetKills()
{
	return PlayerKills;
}
// hide the players tower on the server
void AMainCharacterTest::Server_ToggleTowers_Implementation(bool ToggleTower)
{
	if (Selected != nullptr && !ToggleTower) {

		HideSelected();

	}


}
// used to increment the players individual score 

void AMainCharacterTest::IncrementPlayerScore(int Increment)
{

	if (HasAuthority()) {

		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, FString::Printf(TEXT("Updtaing leaderboard on server")));

		PlayerPoints += Increment;
		UpdateLeaderboard();
		UpdatePlayerScoreUi();
		

	}
	/*else if (IsLocallyControlled()) {
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, FString::Printf(TEXT("updating leaderboard on client")));

		Server_IncrementPlayerScore(Increment);

	}*/


}


// used to decrement the players individual score 

void AMainCharacterTest::DecrementPlayerScore(int Increment)
{

	if (HasAuthority()) {


		PlayerPoints -= Increment; 

		PlayerPoints *= ((int)(PlayerPoints > 0));
		UpdateLeaderboard();
		if (IsLocallyControlled()) {

			UpdatePlayerScoreUi();
		}
	}


}


void AMainCharacterTest::Server_IncrementPlayerScore_Implementation(int increment)
{

	PlayerPoints += increment;
	UpdateLeaderBoardInfo();


}

// increment player kills on server and braodcasted it to the associated client object 
void AMainCharacterTest::IncrementPlayerKills()
{

	// check if has authority and increment kills
	if (HasAuthority()) {
		PlayerKills++; 

		UpdateLeaderboard();
	}
	/*else if (IsLocallyControlled()) {
		Server_UpdatePlayerInfoKills();
	}*/

}

void AMainCharacterTest::Server_UpdatePlayerInfoKills_Implementation()
{

	PlayerKills++;
	UpdateLeaderBoardInfo();


}


// overload of incrementing player kills to pass in a value rather than incrementing by one
void AMainCharacterTest::IncrementPlayerKills(int Increment)
{
	if (HasAuthority()) {
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, FString::Printf(TEXT("Updtaing leaderboard on server")));
		PlayerKills += Increment;
		//UpdateLeaderBoardInfo();
		UpdateLeaderboard();
	}
	/*else if(IsLocallyControlled())
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, FString::Printf(TEXT("Updtaing leaderboard on client")));

		Server_UpdatePlayerInfoKillsInc(Increment);
	}*/

}



void AMainCharacterTest::Server_UpdatePlayerInfoKillsInc_Implementation(int inc)
{
	PlayerKills += inc;
	UpdateLeaderBoardInfo();
}

/// get the players hud widget 
UChargeWidget* AMainCharacterTest::GetPlayerWidget()
{
	return ChargeWidget;
}


