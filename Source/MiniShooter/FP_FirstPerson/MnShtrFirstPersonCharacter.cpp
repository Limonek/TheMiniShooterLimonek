// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrFirstPersonCharacter.h"
#include "MnShtrSaveGame.h"
#include "MnShtrGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Public/TimerManager.h"
#include "DelayAction.h"
#include "MnShtrGameInstance.h"

AMnShtrFirstPersonCharacter::AMnShtrFirstPersonCharacter() :Super()
{
	MaxJumpCount = 3;
	CurrentJumpCount = 0;
}
void AMnShtrFirstPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("PauseMenu", IE_Pressed, this, &AMnShtrFirstPersonCharacter::ShowPauseMenu);

	UWorld* world = GetWorld();
	UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
	size_t i = -1;
	if (gameInstance->CanJump)
	{
		if (PlayerInputComponent->GetNumActionBindings())
		{
			do {
				for (i = 0; i < PlayerInputComponent->GetNumActionBindings(); i++)
				{
					if (PlayerInputComponent->GetActionBinding(i).ActionName == "Jump")
						break;
				}
				if (i == PlayerInputComponent->GetNumActionBindings())
					i = 0;
				else
				{
					PlayerInputComponent->RemoveActionBinding(i);
					++i;
				}

			} while (i);
		}
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMnShtrFirstPersonCharacter::OnStartJump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMnShtrFirstPersonCharacter::OnStopJump);
	}
	if (gameInstance->CanJump)
	{
		PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMnShtrFirstPersonCharacter::StartRun);
		PlayerInputComponent->BindAction("Run", IE_Released, this, &AMnShtrFirstPersonCharacter::StopRun);
	}
}
void AMnShtrFirstPersonCharacter::ShowPauseMenu()
{
	AMnShtrGameModeBase* gameMode = Cast<AMnShtrGameModeBase>(GetWorld()->GetAuthGameMode());
	gameMode->StartShowingStartingWidget();
}
//jumping
void AMnShtrFirstPersonCharacter::Landed(const FHitResult & Hit)
{
	CurrentJumpCount = 0;
}
bool AMnShtrFirstPersonCharacter::CanJumpInternal_Implementation() const
{
	UCharacterMovementComponent *movementComponent = GetCharacterMovement();
	return Super::CanJumpInternal_Implementation() || (movementComponent->MovementMode == MOVE_Falling && CurrentJumpCount > 0 && CurrentJumpCount < MaxJumpCount);
}
void AMnShtrFirstPersonCharacter::OnStartJump()
{
	bPressedJump = true;
	CurrentJumpCount++;
}
void AMnShtrFirstPersonCharacter::OnStopJump()
{
	bPressedJump = false;
}
//jumping end
void AMnShtrFirstPersonCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
void AMnShtrFirstPersonCharacter::StartRun()
{
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}
void AMnShtrFirstPersonCharacter::FellOutOfWorld(const UDamageType &dmgType)
{
	AMnShtrGameModeBase* gameMode = Cast<AMnShtrGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		if (DeadWidgetClass)
		{
			gameMode->ChangeMenuWidget(DeadWidgetClass);
			APlayerController *playerController = GetWorld()->GetFirstPlayerController();
			playerController->SetPause(true);
			this->SetTickableWhenPaused(true);
			playerController->SetInputMode(FInputModeUIOnly());
			int32 UUID = 123;
			if (UWorld* world = GetWorld())
			{
				FLatentActionManager& LatentActionManager = world->GetLatentActionManager();
				if (LatentActionManager.FindExistingAction<FDelayAction>(this, UUID) == NULL)
				{
					FLatentActionInfo LatentActionInfo(0, UUID, TEXT("CountdownFinished"), this);
					LatentActionManager.AddNewAction(this, UUID, new FDelayAction(3, LatentActionInfo));
					UMnShtrGameInstance* gameInstance = Cast<UMnShtrGameInstance>(world->GetGameInstance());
					UGameplayStatics::OpenLevel(world, gameInstance->Level);
				}
			}
		}
	}
}
void AMnShtrFirstPersonCharacter::CountdownFinished()
{
	UWorld *world = GetWorld();
	AMnShtrGameModeBase* gameMode = Cast<AMnShtrGameModeBase>(world->GetAuthGameMode());
	gameMode->ChangeMenuWidget(nullptr);
}
