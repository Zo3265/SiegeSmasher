// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 
#include "SpawnPoint.h" 
#include"../Enemies/EnemyBase.h"
#include "WaveManager.generated.h"

UCLASS()
class SIEGESMASHER_API AWaveManager : public AActor
{

	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWaveManager();



protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemiesToSpawn");
	TArray<AEnemyBase*> EnemiesToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WaveSpawnPoints");
	TArray<ASpawnPoint*> SpawnPoints;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int GetTotalWaveEnemyCount();
	int GetCurrentEnemyWaveCount();
	void UpdateCurrentWave(float deltaTime);
	bool CheckWaveEnd();
	void BeginWave();
	void CalculateNextEnemyWaveCount(float WaveNumFractional);
	void GetNewSpawnPoint();

	void EnemySetUp();
	// variables for wave generation
private:
	float WaveGlobalWaitTimerMax = 5.0f;
	float WaveGlobalWaitTimer = 5.0f;
	int WaveNumber = 0;
	int TotalEnemiesSpawned = 0;
	int WaveEnemyCount = 0;
	int AliveEnemyCount = 0;
	int baseStartingEnemyCount = 8;
	float WavePolynomialConstantOne = 0.7f;
	float WavePolynomialConstantTwo = 0.2f;

	void UpdateSpawning(float DeltaTime);
	void CheckSpawnPoints(float DeltaTime);
	void EvaluateEnemySpawning();
	AEnemyBase* GetExistingInstance(EnemyTypes EnemyType);


	// track current spawn point status
private:
	float CurrentTimeForSpawnPoint = 0.0f;
	int CurrentSpawnPointCap = 0;
	int EnemiesSpawnedOnPoint = 0;
	int CurrentAvailableEnemyIndex = 0;
	bool SpawnDebugTest = true;
	FRandomStream random;
	ASpawnPoint* CurrentSpawnPoint = nullptr;

	//EnemyStorage	
private:

	TArray<AEnemyBase*> AvailableEnemies;
	TMap<EnemyTypes, TArray<AEnemyBase*>> EnemyPools;
	TMap<EnemyTypes, int> EnemyWaveContribution;
	TMap<EnemyTypes, int> EnemyAvailablePoolIndicies;




};
