// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyInheritTest.h"

// Sets default values
AEnemyInheritTest::AEnemyInheritTest()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyInheritTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyInheritTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
int AEnemyInheritTest::CalculateWaveContribution(float FractionalWaveNumber) {

	CurrentWaveContribution = EnemyStartingCount + ceil(FractionalWaveNumber * WavePolynomialConstantOne + (FractionalWaveNumber * FractionalWaveNumber) * WavePolynomialConstantTwo);
	return CurrentWaveContribution;
}
// Called to bind functionality to input
void AEnemyInheritTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

