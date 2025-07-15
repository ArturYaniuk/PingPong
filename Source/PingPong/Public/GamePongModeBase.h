#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamePongModeBase.generated.h"

UCLASS()
class PINGPONG_API AGamePongModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void PostLogin(APlayerController* NewPlayer) override;
};