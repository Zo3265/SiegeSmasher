// Fill out your copyright notice in the Description page of Project Settings.


#include "BalistaTower.h"

// Sets default values
ABalistaTower::ABalistaTower()
{
	bReplicates = true;
	SetReplicateMovement(true);
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BoxColliderForObjectPlacement;
	BallistaBase = CreateDefaultSubobject<UStaticMeshComponent>("BallistaBase"); 
	BallistaBase->SetupAttachment(RootComponent);
	BallistaTurret = CreateDefaultSubobject<UStaticMeshComponent>("BallistaTurret");
	BallistaTurret->SetupAttachment(RootComponent);
	BallistaArrow = CreateDefaultSubobject<UStaticMeshComponent>("BallistaArrow");
	BallistaArrow->SetupAttachment(BallistaTurret);

	BallistaBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BallistaArrow->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BallistaTurret->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StimuliSourceComponent->UnregisterFromPerceptionSystem();

}


void ABalistaTower::BeginPlay() {
  
	Super::BeginPlay(); 



}

void ABalistaTower::Multicast_SetArrowHidden_Implementation(bool HideBallistaArrow)
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("setting ballista arrow hidden %d "), (int)HideBallistaArrow));
	BallistaArrow->SetHiddenInGame(HideBallistaArrow);


}

/// used to control whether or not the mesh used to indciate if the ballista is relaoding to the player is hidden 
void ABalistaTower::HideArrow(bool ShouldHideArrow)
{

	// if we need to unhide/hide the arrow and are the authoritative instance
	if (HasAuthority() && BallistaArrow->bHiddenInGame != ShouldHideArrow) {

		// call a net multi cast from this authoritative instance to update the hidden state of the arrow mesh 
		// ensuring that the ballistas reloading state is accuratley displayed on all connnectd machines 
		Multicast_SetArrowHidden(ShouldHideArrow);

	}


}
// main atcive state for ballista tower
void ABalistaTower::TowerActive(float& DeltaTime) {

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Ballista Tower Active ")));

	// establish a vector from the turret to the assigned enemy target
	FVector BallistaTurretLocation = BallistaTurret->GetComponentLocation();
	FVector ToTarget;
	if (EnemySingleTarget != nullptr)
	{
		ToTarget = EnemySingleTarget->GetActorLocation() - BallistaTurret->GetComponentLocation();
	}
	FVector TargetDir = ToTarget.GetSafeNormal();

	DrawDebugLine(GetWorld(), BallistaTurret->GetComponentLocation(), BallistaTurret->GetComponentLocation()+TargetDir * ToTarget.Length(), FColor::Cyan);

	
	bool LostLOs = World->LineTraceSingleByChannel(LOSResult, BallistaTurretLocation,
		           BallistaTurretLocation + TargetDir * ToTarget.Length(), TowerNoLOSChannel);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("distance to target %f"), ToTarget.SquaredLength()));
	
	if (EnemySingleTarget != nullptr && !LostLOs && !CurrentEnemyOutOfRange && EnemySingleTarget->GetHealth() > 0.0f) {


	     

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Ballista currently active")));
		// used to determine when the ballista can shoot during its rotation towards the enemy ensuring that it doesnt shoot 
		// to early and only when its forward vector is algined according to the define threshold in the blueprint for this tower
		float Alignment = TargetDir.Dot(BallistaTurret->GetForwardVector());
		FVector FromTarget = BallistaTurret->GetComponentLocation() - EnemySingleTarget->GetActorLocation();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("alignment  for turret %f "), Alignment));
		
		FVector PitchVector = FVector(0.0f, 0.0f, TargetDir.Z);
		// take the distance in the x and y axis to detemine the pitch taking into account both axis 
		// to ensure that the ballista accuretly pitchees its turret down or upward to the target 
		float DistanceForPitch = sqrt(ToTarget.X * ToTarget.X + ToTarget.Y * ToTarget.Y);         
		float PitchAngle = atan2f(ToTarget.Z, DistanceForPitch);  
		// get the angle in yaw by calculating the sign of the angle based on the quadrant of the unit circle the point defined by the vector lies in  
		// and get the angle based on the ratio between the y and x of the vector between the enemy target and the turret 
		float YawAngle = atan2f(ToTarget.Y, ToTarget.X);

		// establish a quaterion based on the required rotation angles
		FQuat RequiredRotation = FRotator(FMath::RadiansToDegrees(PitchAngle), FMath::RadiansToDegrees(YawAngle), 0.0f).Quaternion();
		FVector YawAlignedActorForward = GetActorForwardVector();
		
		// lerp between the two rotations using a spherical lerp to make the rotation smooth and less snappy
		FQuat TurretRotation = FQuat::Slerp(BallistaTurret->GetComponentRotation().Quaternion(), (RequiredRotation), RotationLerpSpeed);

		BallistaTurret->SetWorldRotation(TurretRotation);

		//  if the forward vector of the turret is aligned enough and we are not waiting to reset(int this case reload)
		if (Alignment > FovSnappingThreshold && !RequiresReset) {

			// call the multicats to hide the arrow as we just shot 
			HideArrow(true);
			// call the emthod to shoot our proejctile object from the tower projectile base class 
			ShootProjectile(BallistaArrow->GetComponentLocation(), RequiredRotation.Rotator());

		}
		// if we are at a certain portion of our reload unhide the arrow used to indcate the reload and call the multicast to do so
		if (WaitTimeToReset <= MaxWaitTimeToReset * ProjectileReappearPercent) {
			
			HideArrow(false);

		}

		return;
	}

	
	 //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Ballista could not find targets waiting for next overlap")));
	// if the condtiions defined above are not met to continue the active state we update the state on the authority instance and
	// and drop out of the active state for this tower
	if (HasAuthority()) {
		CurrentyActive = false;
		EnemySingleTarget = nullptr;
		NoTargetsInRange = true;
	 }

	

	

	
} 




void ABalistaTower::TowerDormant(float& DeltaTime) {

	// call the generic method implmented in the projectile tower base class to check fo rline of sight on any
	// of the enemies in range 
	TrackEnemies(BallistaTurret->GetComponentLocation());

}

void ABalistaTower::EstablishLineOfSightRays()
{
	//FHitResult HitResult;
	//World->LineTraceSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + FVector::DownVector * GetTargetingRangeSqr(), PlacingSurface); 
	//
	//FVector TriggerBoxHalfExtents = TriggerBoxDim / 2.0f;
	//
	//float TriggerBoxDimXY = TriggerBoxHalfExtents.X * TriggerBoxHalfExtents.X + TriggerBoxHalfExtents.Y * TriggerBoxHalfExtents.Y;
	//GLog->Log(FString::Printf(TEXT("trigger box dim sqr lenght %f"), TriggerBoxDimXY));
	//LOSRayFiringPoint = HitResult.ImpactPoint; 
	//FHitResult CheckForObstacles;
	//for (float Angle = -PI; Angle <= PI; Angle += FMath::DegreesToRadians(RayDirectionAngleInc)) {
	//	
	//	GLog->Log(FString::Printf(TEXT("current angle for LOS directions:%f "), Angle));
	//	LineOfSightRays.Emplace(cos(Angle), sin(Angle), 0.0f);

	//    
	//	bool HasHitWall = World->LineTraceSingleByChannel(CheckForObstacles, LOSRayFiringPoint, LOSRayFiringPoint + LineOfSightRays[LineOfSightRays.Num()-1] * TriggerBoxDimXY, TowerNoLOSChannel);

	//	ObstaclePointsForLos.Add(FVector(CheckForObstacles.ImpactPoint.X, CheckForObstacles.ImpactPoint.Y, LOSRayFiringPoint.Z) * HasHitWall);
	//	//DrawDebugLine(GetWorld(), LOSRayFiringPoint, LOSRayFiringPoint + LineOfSightRays[LineOfSightRays.Num()-1] * (FVector(TriggerBoxDim.X,TriggerBoxDim.Y,0.0f).Length()), FColor::Blue, false, 10000.0f);



	//}


}


// check if the ballista has line of sight from the location of the ballista turret mesh that is attached to the root 
//component of the actor 
bool ABalistaTower::HasLineOfSite(FVector To) {


	FHitResult LOSRes = FHitResult();
	// get a vector from the ballista turret to the target
	FVector BallistaTurretLocation = BallistaTurret->GetComponentLocation();
	FVector ToTarget = To - BallistaTurretLocation;
	//shoot a ray  return if we hit anything along it that can block tower line of sight 
	return !(World->LineTraceSingleByChannel(LOSRes,
		BallistaTurretLocation,
		BallistaTurretLocation +
		ToTarget.GetSafeNormal() * ToTarget.Length(),
		TowerNoLOSChannel));

}




