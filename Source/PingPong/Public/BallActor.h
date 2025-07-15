#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

UCLASS()
class PINGPONG_API ABallActor : public AActor
{
    GENERATED_BODY()

public:
    ABallActor();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BallMesh;
    
    UPROPERTY(VisibleAnywhere)
    USphereComponent* BallCollision;
    FVector BallVelocity;

    UPROPERTY(EditAnywhere, Category = "Ball")
    float BallSpeed = 800.f;

    UFUNCTION()
    void OnBallHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
