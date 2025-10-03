// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

// Sets default values
AWaveManager::AWaveManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Display, TEXT("Constructor called"));


}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Wave Manager Begin play called"));
	BeginWave();





}


// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCurrentWave(DeltaTime);





}

void AWaveManager::UpdateCurrentWave(float DeltaTime)
{

	if (WaveGlobalWaitTimer <= 0.0f && !CheckWaveEnd()) {


		UpdateSpawning(DeltaTime);
		return;
	}

	WaveGlobalWaitTimer -= DeltaTime;




}




bool AWaveManager::CheckWaveEnd() {

	if (WaveEnemyCount == TotalEnemiesSpawned && AliveEnemyCount == 0) {

		WaveNumber++;
		BeginWave();
		WaveGlobalWaitTimer = WaveGlobalWaitTimerMax;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("wave global wait timer reset to %f"), WaveGlobalWaitTimer));

		GLog->Log(FString::Printf(TEXT("wave global wait timer reset to %f"), WaveGlobalWaitTimer));
		return true;
	}
	return false;


}

void AWaveManager::BeginWave()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT(" beggining wave, wave number is %d"), WaveNumber));

	EnemySetUp();
	CurrentSpawnPointCap = ceil((float)WaveEnemyCount / (float)SpawnPoints.Num());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT(" spawn point cap for wave %d"), CurrentSpawnPointCap));
	GLog->Log(FString::Printf(TEXT(" spawn point cap for wave %d"), CurrentSpawnPointCap));
	GetNewSpawnPoint();
}
void AWaveManager::CalculateNextEnemyWaveCount(float WaveNumFractional)
{
	WaveEnemyCount = baseStartingEnemyCount + ceil(WaveNumFractional * WavePolynomialConstantOne + (WaveNumFractional * WaveNumFractional) * WavePolynomialConstantTwo);
	AliveEnemyCount = WaveEnemyCount;
}

void AWaveManager::GetNewSpawnPoint()
{
	if (SpawnPoints.Num() > 0) {

		GLog->Log(TEXT("getting new spawn point"));
		EnemiesSpawnedOnPoint = 0;
		int randIndex = random.RandRange(0, SpawnPoints.Num() - 1);
		CurrentSpawnPoint = SpawnPoints[randIndex];
		CurrentSpawnPoint->ResetCoolDownTimer();

		CurrentTimeForSpawnPoint = CurrentSpawnPoint->GetNewSpawnTime();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT(" new allocated spawn time %f"), CurrentTimeForSpawnPoint));
		GLog->Log(FString::Printf(TEXT(" new allocated spawn time %f"), CurrentTimeForSpawnPoint));
	}
}







void AWaveManager::CheckSpawnPoints(float DeltaTime)
{

	if (CurrentTimeForSpawnPoint <= 0.0f || EnemiesSpawnedOnPoint == CurrentSpawnPointCap) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
			FString::Printf(TEXT("need new spawn point, time for spawn point reached  %f Enemies spawned on point %d"), CurrentTimeForSpawnPoint, EnemiesSpawnedOnPoint));

		GLog->Log(FString::Printf(TEXT("need new spawn point, time for spawn point reached  %f Enemies spawned on point %d"), CurrentTimeForSpawnPoint, EnemiesSpawnedOnPoint));
		GetNewSpawnPoint();
		return;
	}
	CurrentTimeForSpawnPoint -= DeltaTime;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Current time for spawn point %f"), CurrentTimeForSpawnPoint));
	//GLog->Log(FString::Printf(TEXT("Current time for spawn point %f"), CurrentTimeForSpawnPoint));


}





void AWaveManager::EnemySetUp()
{
	// reset values associated with spawning enemies
	CurrentAvailableEnemyIndex = 0;
	TotalEnemiesSpawned = 0;

	for (int i = 0; i < EnemiesToSpawn.Num(); i++) {
		EnemyTypes EnemyType = EnemiesToSpawn[i]->GetEnemyWaveType();
		if (EnemiesToSpawn[i]->GetStartingWave() <= WaveNumber) {

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
				FString::Printf(TEXT(" new enemy added to available enemies %d wave number was %d"), (int)EnemyType, WaveNumber));
			GLog->Log(FString::Printf(TEXT(" new enemy added to available enemies %d wave number was %d"), (int)EnemyType, WaveNumber));

			AvailableEnemies.Add(EnemiesToSpawn[i]);
			EnemyPools.Add(EnemyType, {});
			EnemyAvailablePoolIndicies.Add(EnemyType, 0);
			EnemyWaveContribution.Add(EnemyType, 0);
			continue;
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
			FString::Printf(TEXT(" enemy excluded from this wave, wave number was %d enemy types was %d enemy starting wave"), WaveNumber, (int)EnemyType, EnemiesToSpawn[i]->GetStartingWave()));
		GLog->Log(FString::Printf(TEXT(" enemy excluded from this wave, wave number was %d enemy types was %d enemy starting wave"), WaveNumber, (int)EnemyType, EnemiesToSpawn[i]->GetStartingWave()));


	}
	GLog->Log(FString::Printf(TEXT("number of available enemies %d"), (int)AvailableEnemies.Num()));

	for (int i = 0; i < AvailableEnemies.Num(); i++) {

		int NewEnemyWaveContrib = AvailableEnemies[i]->CalculateWaveContribution(WaveNumber);
		EnemyTypes EnemyType = AvailableEnemies[i]->GetEnemyWaveType();
		WaveEnemyCount += NewEnemyWaveContrib;
		EnemyAvailablePoolIndicies[EnemyType] = 0;
		EnemyWaveContribution[EnemyType] = NewEnemyWaveContrib;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
			FString::Printf(TEXT(" new enemy added to  enemy pools type %d  wave number %d"), (int)EnemyType, WaveNumber));
		GLog->Log(FString::Printf(TEXT(" new enemy added to  enemy pools type %d  wave number %d"), (int)EnemyType, WaveNumber));
	}

	AliveEnemyCount = WaveEnemyCount;


	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
		FString::Printf(TEXT(" total enemies for this wave : % d"), AliveEnemyCount));
	GLog->Log(FString::Printf(TEXT(" total enemies for this wave : % d"), AliveEnemyCount));


}

void AWaveManager::UpdateSpawning(float DeltaTime)
{

	if (TotalEnemiesSpawned != WaveEnemyCount) {
		CheckSpawnPoints(DeltaTime);
		EvaluateEnemySpawning();

	}




}

void AWaveManager::EvaluateEnemySpawning()
{
	if (CurrentSpawnPoint->IsAvailable()) {


		int randomAvailableEnemyIndex = random.RandRange(CurrentAvailableEnemyIndex, AvailableEnemies.Num() - 1);
		GLog->Log(FString::Printf(TEXT("Current number of enemies spawned"), TotalEnemiesSpawned));
		GLog->Log(FString::Printf(TEXT("available index before accessing available enemies"), CurrentAvailableEnemyIndex));
		GLog->Log(FString::Printf(TEXT("random index available enemies %d"), randomAvailableEnemyIndex));
		AEnemyBase* CurrentEnemyToSpawn = AvailableEnemies[randomAvailableEnemyIndex];
		AEnemyBase* PotentialEnemyInstance = GetExistingInstance(CurrentEnemyToSpawn->GetEnemyWaveType());
		if (PotentialEnemyInstance == nullptr) {

			GLog->Log(TEXT("could not get existing enemy instance attempting to spawn new enemy instance"));
			PotentialEnemyInstance = CurrentSpawnPoint->SpawnEnemy(CurrentEnemyToSpawn);
			EnemyPools[CurrentEnemyToSpawn->GetEnemyWaveType()].Add(PotentialEnemyInstance);
		}

		EnemyWaveContribution[CurrentEnemyToSpawn->GetEnemyWaveType()] -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Enemy wave contirbtuion  for enemy type %d  is now %d"), (int)CurrentEnemyToSpawn->GetEnemyWaveType(), EnemyWaveContribution[CurrentEnemyToSpawn->GetEnemyWaveType()]));
		GLog->Log(FString::Printf(TEXT("Enemy wave contirbtuion  for enemy type %d  is now %d"), (int)CurrentEnemyToSpawn->GetEnemyWaveType(), EnemyWaveContribution[CurrentEnemyToSpawn->GetEnemyWaveType()]));
		if (!(EnemyWaveContribution[CurrentEnemyToSpawn->GetEnemyWaveType()]))
		{
			AEnemyBase* temp = AvailableEnemies[CurrentAvailableEnemyIndex];
			AvailableEnemies[CurrentAvailableEnemyIndex] = AvailableEnemies[randomAvailableEnemyIndex];
			AvailableEnemies[randomAvailableEnemyIndex] = temp;
			CurrentAvailableEnemyIndex++;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Enemy wave contirbtuion reached 0 for enemy type %d new available index is %d"), (int)CurrentEnemyToSpawn->GetEnemyWaveType(), CurrentAvailableEnemyIndex));
			GLog->Log(FString::Printf(TEXT("Enemy wave contirbtuion reached 0 for enemy type %d new available index is %d"), (int)CurrentEnemyToSpawn->GetEnemyWaveType(), CurrentAvailableEnemyIndex));

		}

		TotalEnemiesSpawned++;
		EnemiesSpawnedOnPoint++;

	}
}



AEnemyBase* AWaveManager::GetExistingInstance(EnemyTypes EnemyType)
{

	int& availableIndex = EnemyAvailablePoolIndicies[EnemyType];
	if (availableIndex != EnemyPools[EnemyType].Num() && !EnemyPools[EnemyType][availableIndex]->IsActorTickEnabled()) {

		availableIndex++;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
			FString::Printf(TEXT(" found existing available instance new available index is %d previous index %d"), EnemyAvailablePoolIndicies[EnemyType], EnemyAvailablePoolIndicies[EnemyType] - 1));
		GLog->Log(FString::Printf(TEXT(" found existing available instance new available index is %d previous index %d"), EnemyAvailablePoolIndicies[EnemyType], EnemyAvailablePoolIndicies[EnemyType] - 1));

		return CurrentSpawnPoint->SpawnAndResetExistingEnemyInstance(EnemyPools[EnemyType][availableIndex - 1]);

	}
	return nullptr;
}

int AWaveManager::GetTotalWaveEnemyCount()
{
	return WaveEnemyCount;
}

int AWaveManager::GetCurrentEnemyWaveCount()
{
	return AliveEnemyCount;
}

