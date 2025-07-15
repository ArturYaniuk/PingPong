// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPong/Public/BasePaddle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"


void ABasePaddle::MoveRight(float Value)
{
	if (Controller && IsLocallyControlled() && FMath::Abs(Value) > 0.01f)
	{
		FVector Offset = GetActorRightVector() * Value * MovementComponent->MaxSpeed * GetWorld()->GetDeltaSeconds();
		FVector NewLocation = GetActorLocation() + Offset;

		SetActorLocation(NewLocation);
		Server_SendMovement(NewLocation);
	}
}

void ABasePaddle::Server_SendMovement_Implementation(FVector NewLocation)
{
	Multicast_ReplicateMovement(NewLocation);
}

void ABasePaddle::Multicast_ReplicateMovement_Implementation(FVector NewLocation)
{
	if (!IsLocallyControlled()) 
	{
		SetActorLocation(NewLocation);
	}
}

// Sets default values
ABasePaddle::ABasePaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterMesh1P"));
	RootComponent = Mesh1P;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->MaxSpeed = 600.f;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	FirstPersonCameraComponent->SetupAttachment(SpringArmComponent);

	bReplicates = true;
    AActor::SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void ABasePaddle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ABasePaddle::MoveRight);
}

