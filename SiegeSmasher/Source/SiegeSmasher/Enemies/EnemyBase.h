// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UENUM(Blueprintable)
enum EnemyTypes
{
	BASE,
	BASE1,


};


UCLASS()
class SIEGESMASHER_API AEnemyBase : public ACharacter
{

	GENERATED_BODY()

public:
	AEnemyBase();

protected:

	virtual void BeginPlay() override;
	int EnemyTest();
	int EnemyStartingCount = 8;
	
	float WavePolynomialConstantOne = 0.7f;
	float WavePolynomialConstantTwo = 0.2f;
	int CurrentWaveContribution = 0;
	
	EnemyTypes EnemyType = BASE;
	float CurrentHealth = 100.0f; 

	float MaxHealth = 100.0f;

	int StartingWave = 0; // wave 0 = 1(starts counting from 0)
public:

	virtual void Tick(float DeltaTime) override;
	virtual int CalculateWaveContribution(float FractionalWaveNumber);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// method used for objects pooling can be overidden by defining it in a child class 
	// but i suggest calling the AEnemyBase class method 
	// by doing AEnemyBase::ResetOnSpawn() inside your overidden method
	virtual void ResetOnSpawn();
	int GetCurrentWaveContribution();
	void SetCurrentWaveContribution(int WaveContrib);
	int GetStartingWave();


	EnemyTypes GetEnemyWaveType();
};
