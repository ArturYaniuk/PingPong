#include "GamePongModeBase.h"

#include "EngineUtils.h"
#include "GamePongStateBase.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"


void AGamePongModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
}

void AGamePongModeBase::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    
    Scores.Init(0, 2); 
}

void AGamePongModeBase::StartMatch()
{
    SpawnNewBall();
}

void AGamePongModeBase::AddScore(int32 PlayerIndex)
{
    if (AGamePongStateBase* GS = GetGameState<AGamePongStateBase>())
    {
        GS->AddScore(PlayerIndex);
    }
}

void AGamePongModeBase::SpawnNewBall()
{
    if (!BallClass) return;

    FVector SpawnLocation(0.f, 0.f, 70.f); 
    FRotator SpawnRotation = FRotator::ZeroRotator;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<ABallActor>(BallClass, SpawnLocation, SpawnRotation, SpawnParams);
}

void AGamePongModeBase::TryStartMatch(APlayerPongController* PlayerController)
{
    if (!PlayerController) return;

    if (!JoinedPlayers.Contains(PlayerController))
    {
        JoinedPlayers.Add(PlayerController);
    }

    if (JoinedPlayers.Num() == 1)
    {
        PlayerController->Client_ShowWaitingMessage();
    }
    else if (JoinedPlayers.Num() == 2)
    {
        for (auto* PC : JoinedPlayers)
        {
            PC->Client_StartMatch();
        }
        StartMatch();
    }
}

APawn* AGamePongModeBase::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer,
                                                                     const FTransform& SpawnTransform)
{
    if (DefaultPawnClass == nullptr) return nullptr;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    return GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnTransform, SpawnParams);
}


AActor* AGamePongModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
    int32 PlayerIndex = GameState->PlayerArray.IndexOfByKey(Player->PlayerState);

    FString DesiredTag = (PlayerIndex == 0) ? TEXT("Player1") : TEXT("Player2");
    
    for (APlayerStart* Start : TActorRange<APlayerStart>(GetWorld()))
    {
        if (Start->PlayerStartTag == FName(*DesiredTag))
        {
            return Start;
        }
    }

    return Super::ChoosePlayerStart_Implementation(Player);
}
