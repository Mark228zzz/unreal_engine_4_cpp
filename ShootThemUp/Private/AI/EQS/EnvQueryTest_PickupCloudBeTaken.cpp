// Stoot Them Up Game, All Rights Reserved.


#include "AI/EQS/EnvQueryTest_PickupCloudBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUBasePickup.h"

UEnvQueryTest_PickupCloudBeTaken::UEnvQueryTest_PickupCloudBeTaken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupCloudBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const auto DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	const bool WantsBeTakeble = BoolValue.GetValue();

	for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto PickupActor = Cast<ASTUBasePickup>(ItemActor);
		if(!PickupActor) return;

		const auto CouldBeTaken = PickupActor->CouldBeTaken();
		It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakeble);
	}
}
