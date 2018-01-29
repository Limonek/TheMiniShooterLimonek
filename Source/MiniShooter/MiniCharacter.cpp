// Fill out your copyright notice in the Description page of Project Settings.

//#include "MnShtrFirstPersonCharacter.h"
#include "MiniCharacter.h"
#include "MnShtrSaveGame.h"
#include "MnShtrGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Public/TimerManager.h"
#include "MnShtrGameInstance.h"
#include "DelayAction.h"


// Sets default values
AMiniCharacter::AMiniCharacter() :Super()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitPoints = 100;
	//Experiance = 0;
	//from MnShtrFirstPersonCharacter
	MaxJumpCount = 3;
	CurrentJumpCount = 0;
	//end from MnShtrFirstPersonCharacter
}

// Called when the game starts or when spawned
void AMiniCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMiniCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void AMiniCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

void AMiniCharacter::GetRekt(float dmg)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("BB const"));
	HitPoints -= dmg;
	if (HitPoints <= 0) {
		//zabijanie gracza
	}
}

void AMiniCharacter::AddExp(float xp)
{
	Exp += xp;
}

//from MnShtrFirstPersonCharacter

//AMiniCharacter::AMnShtrFirstPersonCharacter() :Super()
//{
//	MaxJumpCount = 3;
//	CurrentJumpCount = 0;
//}
void AMiniCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("PauseMenu", IE_Pressed, this, &AMiniCharacter::ShowPauseMenu);

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
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMiniCharacter::OnStartJump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMiniCharacter::OnStopJump);
	}
	if (gameInstance->CanJump)
	{
		PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMiniCharacter::StartRun);
		PlayerInputComponent->BindAction("Run", IE_Released, this, &AMiniCharacter::StopRun);
	}
}
void AMiniCharacter::ShowPauseMenu()
{
	AMnShtrGameModeBase* gameMode = Cast<AMnShtrGameModeBase>(GetWorld()->GetAuthGameMode());
	gameMode->StartShowingStartingWidget();
}
//jumping
void AMiniCharacter::Landed(const FHitResult & Hit)
{
	CurrentJumpCount = 0;
}
bool AMiniCharacter::CanJumpInternal_Implementation() const
{
	UCharacterMovementComponent *movementComponent = GetCharacterMovement();
	return Super::CanJumpInternal_Implementation() || (movementComponent->MovementMode == MOVE_Falling && CurrentJumpCount > 0 && CurrentJumpCount < MaxJumpCount);
}
void AMiniCharacter::OnStartJump()
{
	bPressedJump = true;
	CurrentJumpCount++;
}
void AMiniCharacter::OnStopJump()
{
	bPressedJump = false;
}
//jumping end
void AMiniCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
void AMiniCharacter::StartRun()
{
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}
void AMiniCharacter::FellOutOfWorld(const UDamageType &dmgType)
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
void AMiniCharacter::CountdownFinished()
{
	UWorld *world = GetWorld();
	AMnShtrGameModeBase* gameMode = Cast<AMnShtrGameModeBase>(world->GetAuthGameMode());
	gameMode->ChangeMenuWidget(nullptr);
}
//end from MnShtrFirstPersonCharacter