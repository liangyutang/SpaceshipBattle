// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->SetupAttachment(RootComponent);

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>("ShipSM");
	ShipSM->SetupAttachment(CollisionComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(ShipSM);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	Speed = 2500.f;
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());
	//��ʾ���
	PC->bShowMouseCursor = true;
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtCursor();

	Move(DeltaTime);
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (const APlayerController* PlayerController=CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Move, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Up)
		{
			EnhancedInputComponent->BindAction(IA_Up, ETriggerEvent::Triggered, this, &ASpaceShip::MoveUp);
		}

		if (IA_Right)
		{
			EnhancedInputComponent->BindAction(IA_Right, ETriggerEvent::Triggered, this, &ASpaceShip::MoveRight);
		}
	}


	
}

void ASpaceShip::Move(float DeltaTime)
{
	//FApp::GetDeltaTime();
	AddActorWorldOffset(ConsumeMovementInputVector()* Speed*DeltaTime,true) ;
}

void ASpaceShip::LookAtCursor()
{
	FVector MouseLocation, MouseDirection;
    PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	const FVector TargetLocation = FVector(MouseLocation.X, MouseLocation.Y, GetActorLocation().Z);
	//�ɻ��������ĽǶ�
	const FRotator NowRotatory= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

	SetActorRotation(NowRotatory);
}

void ASpaceShip::MoveUp(const FInputActionValue& InputValue)
{
	const float Value = InputValue.GetMagnitude();
	AddMovementInput(FVector::ForwardVector,Value);
}

void ASpaceShip::MoveRight(const FInputActionValue& InputValue)
{
	const float Value = InputValue.GetMagnitude();
	AddMovementInput(FVector::RightVector,Value);
}

