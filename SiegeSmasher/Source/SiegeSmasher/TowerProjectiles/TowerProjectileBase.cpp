// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerProjectileBase.h"
#include "../MyMainCharacterTest.h"
// Sets default values
ATowerProjectileBase::ATowerProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	bReplicates = true;
	SetReplicateMovement(true);
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh"); 
	ProjectileMesh->SetCollisionProfileName(FName("TowerProjectile"));
	RootComponent = ProjectileMesh;
	PlayerRef = nullptr; 

	//ProjectileMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}


void ATowerProjectileBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATowerProjectileBase, InitalPitch); 
	DOREPLIFETIME(ATowerProjectileBase, Target);

	
}

// Called when the game starts or when spawned
void ATowerProjectileBase::BeginPlay()
{

	Super::BeginPlay();
	// add the binding to the collision of the static mesh for it to damage enemies on collision
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &ATowerProjectileBase::OnOverLapBegin);
	World = GetWorld();

}

void ATowerProjectileBase::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	// if we can succesfully cast to an enemy
		if (AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor)) {

			// call the generic damage functionn across all enemies which will dmaage the enemy on the server side and replciate to all clients
			if (HasAuthority()) {
				Enemy->DamageEnemy(Damage, PlayerRef);
			}



		}
		// if the projectile overlaps with anything destroy it 
	    World->DestroyActor(this);






} 





// Called every frame
void ATowerProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	MoveToTarget(DeltaTime);


}

void ATowerProjectileBase::SetEnemyTarget(AActor* Enemy)
{

	Target = Enemy;

}

void ATowerProjectileBase::MoveToTarget(float DeltaTime)
{
	// track the target if they exist 
	if (Target != nullptr) {
		TargetPosition = Target->GetActorLocation(); 


	}

	
	// lerp the projectile towards the enemy target while adjusting its rotation accordingly 
	FVector CurrentDifference = TargetPosition - GetActorLocation(); 

	double currentRotationAngleYaw = atan2(CurrentDifference.Y,CurrentDifference.X);  


	FQuat TravelRot = FRotator(InitalPitch, FMath::RadiansToDegrees(currentRotationAngleYaw),0.0f).Quaternion();



	SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), TargetPosition, DeltaTime, ProjectileSpeed));


	SetActorRotation(TravelRot);


}

void ATowerProjectileBase::SetPlayerRef(AMainCharacterTest* PlayerPtr) {
	PlayerRef = PlayerPtr;
}




void ATowerProjectileBase::SetInitialPitch(float Pitch)
{
	InitalPitch = Pitch;
}



