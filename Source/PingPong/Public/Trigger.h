// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Trigger.generated.h"

class USphereComponent;

UCLASS()
class PINGPONG_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	ATrigger();

	UPROPERTY(EditAnywhere, Category="Score")
	int32 PlayerIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;
};
