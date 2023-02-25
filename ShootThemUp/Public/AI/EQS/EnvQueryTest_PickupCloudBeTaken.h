// Stoot Them Up Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCloudBeTaken.generated.h"

UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PickupCloudBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()
	
public:
	UEnvQueryTest_PickupCloudBeTaken(const FObjectInitializer& ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
