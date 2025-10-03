// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int  AEnemyBase::CalculateWaveContribution(float FractionalWaveNumber)
{

	CurrentWaveContribution = EnemyStartingCount + ceil(FractionalWaveNumber * WavePolynomialConstantOne + (FractionalWaveNumber * FractionalWaveNumber) * WavePolynomialConstantTwo);
	return CurrentWaveContribution;
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::ResetOnSpawn()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	CurrentHealth = MaxHealth;


}

int AEnemyBase::GetCurrentWaveContribution()
{
	return CurrentWaveContribution;
}

void AEnemyBase::SetCurrentWaveContribution(int WaveContrib)
{
	CurrentWaveContribution = WaveContrib;
}

int AEnemyBase::GetStartingWave()
{
	return StartingWave;
}

EnemyTypes AEnemyBase::GetEnemyWaveType()
{
	return EnemyType;
}

