#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GamePongStateBase.generated.h"

UCLASS()
class PINGPONG_API AGamePongStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AGamePongStateBase();

	UPROPERTY(ReplicatedUsing = OnRep_ScoreChanged, BlueprintReadOnly)
	TArray<int32> PlayerScores;

	UFUNCTION()
	void OnRep_ScoreChanged();

	UFUNCTION(BlueprintCallable)
	FString GetFormattedScore() const;

	void AddScore(int32 PlayerIndex);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
