// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"../Enemies/EnemyBase.h"
#include "SpawnPoint.generated.h"

UCLASS()
class SIEGESMASHER_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoint");
	float AllocatedSpawnTimeMin = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoint");
	float AllocatedSpawnTimeMax = 2.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoint");
	float CoolDownTimerMin = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoint");
	float CoolDownTimerMax = 2.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetNewSpawnTime();
	AEnemyBase* SpawnEnemy(AEnemyBase* EnemyRef);
	AEnemyBase* SpawnAndResetExistingEnemyInstance(AEnemyBase* EnemyRef);
	void ResetCoolDownTimer();
	bool IsAvailable();
private:
	FRandomStream random;
	float CoolDownTimer = 0.0f;





};
