// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicProjectile.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "GeneralEngineSettings.h"
#include "Health.h"
#include "Kismet/GameplayStatics.h"
#include "ParticleDefinitions.h"
#include <algorithm>

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Models/Bullet.Bullet"));
	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = _MeshComponent;

	_MeshComponent->SetStaticMesh(Mesh.Object);
	SetActorEnableCollision(true);
	_MeshComponent->SetNotifyRigidBodyCollision(true);
	_MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	_MeshComponent->SetSimulatePhysics(true);
	_MeshComponent->SetEnableGravity(false);
	_MeshComponent->GetBodyInstance()->bLockZTranslation = true;
	this->OnActorHit.AddDynamic(this, &ABasicProjectile::OnHit);
	_MeshComponent->SetCollisionProfileName(TEXT("Bullet"));
	
}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (TActorIterator<AActor> itr(GetWorld()); itr; ++itr)
	{
		if (itr->GetName() == ("Player_Blueprint"))
		{
			_PlayerPos = itr->GetActorLocation();
			break;
		}
	}

	float r = FVector::Dist(_PlayerPos, this->GetActorLocation());

	FVector dir = _PlayerPos - this->GetActorLocation();
	dir.Normalize();

	_Velocity += dir * _GravityModifier;

	float angle = std::atan2(_Velocity.Y, _Velocity.X) * 57.2958;

	this->SetActorLocation(this->GetActorLocation() + _Velocity * DeltaTime,true, NULL);
	this->SetActorRotation(FRotator(0, angle + 180, 0));
}

/** Function to handle the projectile hitting something */
UFUNCTION()
void ABasicProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("We got a collision."));

	TArray<UHealth*> hc;
	OtherActor->GetComponents(hc);
	
	for (UHealth* health : hc)
	{
		health->Damage(50);
	}

	UParticleSystemComponent* MyParticleSystem = UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		Explode,
		GetActorLocation(),
		GetActorRotation(),
		false
	);

	Destroy();
}
