#pragma once
#include "Components/SplineMeshComponent.h"
#include "TetherConnection.generated.h"

class ATether;

USTRUCT(BlueprintType)
struct FTetherConnection
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATether* Tether;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USplineMeshComponent> Spline;
};
