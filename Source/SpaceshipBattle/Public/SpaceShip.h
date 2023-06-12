// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "SpaceShip.generated.h"

UCLASS()
class SPACESHIPBATTLE_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

	UPROPERTY(EditAnywhere,Category="Move")
	float Speed;


protected:

	UPROPERTY(VisibleAnywhere,Category="Component")
	UStaticMeshComponent* ShipSM;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPoint;

	UPROPERTY()
	APlayerController* PC;

	UPROPERTY(EditAnywhere,Category="Fire")
	TSubclassOf<class ABullet> Bullet;

	FTimerHandle TimerHandle_BetweenShot;

	float TimeBetweenShot;

	FTimerHandle TimerHandle_RestartGame;

	bool bIsDead;

	UPROPERTY(VisibleAnywhere,Category="component")
	UParticleSystemComponent* ThrusterParticle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void LookAtCursor();

	void MoveUp(const FInputActionValue& InputValue);

	void MoveRight(const FInputActionValue& InputValue);

	void Fire();

	void StartFire();

	void EndFire();

	void ReStartLevel();

	void OnDeath();

	UPROPERTY(EditAnywhere,Category="Sound")
	class USoundCue* GameOverCue;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* ShootCue;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(float DeltaTime);

	FORCEINLINE bool GetBDead() const { return bIsDead; }

private:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Move | Context",meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UInputMappingContext> IMC_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move | Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_Up;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move | Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_Right;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move | Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_Fire;
};
