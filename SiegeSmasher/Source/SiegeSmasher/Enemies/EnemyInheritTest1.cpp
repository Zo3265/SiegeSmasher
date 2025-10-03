// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyInheritTest1.h"

// Sets default values
AEnemyInheritTest1::AEnemyInheritTest1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyType = BASE1;
}

// Called when the game starts or when spawned
void AEnemyInheritTest1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyInheritTest1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
int AEnemyInheritTest1::CalculateWaveContribution(float FractionalWaveNumber) {

	CurrentWaveContribution = 2;

	return CurrentWaveContribution;
}
// Called to bind functionality to input
void AEnemyInheritTest1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

