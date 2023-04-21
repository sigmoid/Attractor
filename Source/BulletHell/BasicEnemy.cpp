// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemy.h"
#include "GeneralEngineSettings.h"
#include "EngineUtils.h"
#include "Health.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundCue.h"
#include "CoreMinimal.h"
#include "Engine.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));

	_Mesh->SetNotifyRigidBodyCollision(true);
	RootComponent = _Mesh;
	_Mesh->SetCollisionProfileName(TEXT("Vehicle"));
	_Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	UHealth* _HealthComponent = CreateDefaultSubobject <UHealth>("health");
	_HealthComponent->_Health = health;


	AudioComponent = CreateDefaultSubobject<UAudioComponent>(
		TEXT("AudioComp")
		);
	AudioComponent->bStopWhenOwnerDestroyed = false;
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (CanTrackPlayer)
	{
	FVector pos;
		for (TActorIterator<AActor> itr(GetWorld()); itr; ++itr)
		{
			if (itr->GetName() == ("Player_Blueprint"))
			{
				pos = itr->GetActorLocation();
				break;
			}
		}

		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), pos);
		PlayerRot.Yaw += 180;
		SetActorRotation(PlayerRot);

	}

}

void ABasicEnemy::Destroyed()
{
	AudioComponent->Play();
	Super::Destroyed();
	
}

