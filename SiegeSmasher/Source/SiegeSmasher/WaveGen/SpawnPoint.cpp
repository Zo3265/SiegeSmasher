// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ASpawnPoint::GetNewSpawnTime()
{
	return random.FRandRange(AllocatedSpawnTimeMin, AllocatedSpawnTimeMax);
}

AEnemyBase* ASpawnPoint::SpawnEnemy(AEnemyBase* EnemyRef)
{
	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<AEnemyBase>(EnemyRef->GetClass(), GetActorTransform(), spawnParameters);

}

AEnemyBase* ASpawnPoint::SpawnAndResetExistingEnemyInstance(AEnemyBase* EnemyRef)
{
	EnemyRef->ResetOnSpawn();
	EnemyRef->SetActorLocation(GetActorLocation());
	return EnemyRef;
}

void ASpawnPoint::ResetCoolDownTimer()
{

	CoolDownTimer = random.FRandRange(CoolDownTimerMin, CoolDownTimerMax);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("reseting cool donw timer inside of spawn point new value is %f"), CoolDownTimer));
	GLog->Log(FString::Printf(TEXT("reseting cool donw timer inside of spawn point new value is %f"), CoolDownTimer));



}

bool ASpawnPoint::IsAvailable()
{

	if (CoolDownTimer <= 0.0f) {
		ResetCoolDownTimer();
	}
	CoolDownTimer -= GetWorld()->GetDeltaSeconds();
	GLog->Log(FString::Printf(TEXT("current cool donw timer inside of current spawn point is %f"), CoolDownTimer));

	return CoolDownTimer <= 0.0f;
}





