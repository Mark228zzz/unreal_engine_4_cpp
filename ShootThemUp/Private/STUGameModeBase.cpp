// Stoot Them Up Game, All Rights Reserved.


#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "AIController.h"
#include "UI/STUGameHUD.h"
#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All);

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
	PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();

	CurrentRound = 1;
	StartRound();
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}


void ASTUGameModeBase::SpawnBots()
{
	if(!GetWorld()) return;

	for(int32 i = 0; i < GameData.PlayerNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STUAIContoller = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(STUAIContoller);
	}
}

void ASTUGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);
}
void ASTUGameModeBase::GameTimerUpdate()
{
	if(--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if(CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		} else
		{
			UE_LOG(LogSTUGameModeBase, Display, TEXT("====GAME OVER===="));
			LogPlayerInfo();
		}
	}
}

void ASTUGameModeBase::ResetPlayers()
{
	if(!GetWorld()) return;

	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}
void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
	if(Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASTUGameModeBase::CreateTeamsInfo()
{
	UE_LOG(LogSTUGameModeBase, Warning, TEXT("111111111111"));
	if(!GetWorld()) return;

	int32 TeamID = 1;
	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	UE_LOG(LogSTUGameModeBase, Warning, TEXT("22222222222222"));
	if(TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	UE_LOG(LogSTUGameModeBase, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());
	return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColor(AController* Controller)
{
	UE_LOG(LogSTUGameModeBase, Warning, TEXT("33333333333"));
	if(!Controller) return;

	const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
	if(!Character) return;

	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	if(!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTUGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<ASTUPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<ASTUPlayerState>(VictimController->PlayerState) : nullptr;

	if(KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if(VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
}

void ASTUGameModeBase::LogPlayerInfo()
{
	if(!GetWorld()) return;

	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		PlayerState->LogInfo();
	}
}
