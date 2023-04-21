// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticleDefinitions.h"
#include "BasicProjectile.generated.h"

UCLASS()
class BULLETHELL_API ABasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector _Velocity;

	UPROPERTY(EditAnywhere)
	float _GravityModifier = 100;


	UPROPERTY(EditAnywhere)
	UParticleSystem* Explode;

private:
	FVector _PlayerPos;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* _MeshComponent;

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	/** Function to handle the projectile hitting something */
	//virtual void ReceiveActorBeginOverlap(class AActor* overlapping_actor) override;

	
};
