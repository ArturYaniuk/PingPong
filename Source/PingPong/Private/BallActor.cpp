#include "BallActor.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

ABallActor::ABallActor()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    AActor::SetReplicateMovement(true);
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    BallCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BallCollision"));
    RootComponent = BallMesh;

    BallCollision->SetupAttachment(BallMesh);

    BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BallMesh->SetCollisionProfileName(TEXT("BlockAll"));
    BallMesh->SetNotifyRigidBodyCollision(true);
    BallMesh->SetSimulatePhysics(false); 
    BallMesh->SetIsReplicated(true);

    BallMesh->OnComponentHit.AddDynamic(this, &ABallActor::OnBallHit);
}

void ABallActor::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        FVector RandomDirection = FVector(FMath::RandBool() ? 1 : -1, FMath::RandRange(-1.f, 1.f), 0.f).GetSafeNormal();
        BallVelocity = RandomDirection * BallSpeed;
    }
}

void ABallActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!HasAuthority()) return;

    FVector NewLocation = GetActorLocation() + BallVelocity * DeltaTime;
    
    SetActorLocation(NewLocation, true); 
  
}

void ABallActor::OnBallHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                           UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!HasAuthority()) return;
    
    if (!OtherActor || !OtherComp || Hit.Normal.IsNearlyZero())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid hit."));
        return;
    }
    
    FVector Normal = Hit.Normal.GetSafeNormal();
    FVector Reflected = BallVelocity - 2.f * FVector::DotProduct(BallVelocity, Normal) * Normal;

    BallVelocity = Reflected.GetSafeNormal() * BallSpeed;

    UE_LOG(LogTemp, Warning, TEXT("Reflected Velocity: %s (Hit from %s)"), *BallVelocity.ToString(), *OtherActor->GetName());
}

