// Stoot Them Up Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	bool DoFullDamage = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
