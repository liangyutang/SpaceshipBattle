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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LookAtCursor();

	void MoveUp(const FInputActionValue& InputValue);

	void MoveRight(const FInputActionValue& InputValue);

	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(float DeltaTime);

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
