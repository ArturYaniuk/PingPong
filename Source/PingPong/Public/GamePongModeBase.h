#pragma once

#include "CoreMinimal.h"
#include "BallActor.h"
#include "PlayerPongController.h"
#include "GameFramework/GameModeBase.h"
#include "GamePongModeBase.generated.h"

UCLASS()
class PINGPONG_API AGamePongModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void PostLogin(APlayerController* NewPlayer) override;

    virtual void OnConstruction(const FTransform& Transform) override;

    void StartMatch();
    void TryStartMatch(APlayerPongController* PlayerController);
    
    void SpawnNewBall();
    void AddScore(int32 PlayerIndex);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<int32> Scores;

protected:
    virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;

    virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:

    UPROPERTY()
    TArray<APlayerPongController*> JoinedPlayers;

    UPROPERTY(EditDefaultsOnly, Category="Game")
    TSubclassOf<AActor> BallClass;

    
    
};