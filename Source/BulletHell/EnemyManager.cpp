// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyManager.h"
#include "Kismet/GameplayStatics.h"
#include "BasicEnemy.h"
#include "EngineUtils.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	bool isahit = false;
	for (TActorIterator<ABasicEnemy> itr(GetWorld()); itr; ++itr)
	{
		isahit = true;
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), NextLevel, true);
}

