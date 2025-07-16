#include "GamePongStateBase.h"
#include "Net/UnrealNetwork.h"

AGamePongStateBase::AGamePongStateBase()
{
	PlayerScores.Init(0, 2); 
	bReplicates = true;
}

void AGamePongStateBase::AddScore(int32 PlayerIndex)
{
	if (HasAuthority() && PlayerScores.IsValidIndex(PlayerIndex))
	{
		PlayerScores[PlayerIndex]++;
		OnRep_ScoreChanged(); 
	}
}

void AGamePongStateBase::OnRep_ScoreChanged()
{
	UE_LOG(LogTemp, Log, TEXT("Score updated: %d : %d"), PlayerScores[0], PlayerScores[1]);
}

FString AGamePongStateBase::GetFormattedScore() const
{
	return FString::Printf(TEXT("%d : %d"), PlayerScores[0], PlayerScores[1]);
}

void AGamePongStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGamePongStateBase, PlayerScores);
}
