// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrFirstPersonCharacter.h"
#include "MnShtrSaveGame.h"
#include "MnShtrGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Public/TimerManager.h"
#include "DelayAction.h"

AMnShtrFirstPersonCharacter::AMnShtrFirstPersonCharacter() :Super()
{
	MaxJumpCount = 3;
	CurrentJumpCount = 0;
}

void AMnShtrFirstPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("PauseMenu", IE_Pressed, this, &AMnShtrFirstPersonCharacter::ShowPauseMenu);
	PlayerInputComponent->BindAction("Save", IE_Released, this, &AMnShtrFirstPersonCharacter::SaveGame);
	PlayerInputComponent->BindAction("Load", IE_Released, this, &AMnShtrFirstPersonCharacter::LoadGame);
	size_t i = -1;
	do {
		for (i = 0; i < PlayerInputComponent->GetNumActionBindings(); i++)
		{
			if (PlayerInputComponent->GetActionBinding(i).ActionName == "Jump")
				break;
		}
		if (i == PlayerInputComponent->GetNumActionBindings())
			i = 0;
		else
			PlayerInputComponent->RemoveActionBinding(i);

	} while (i);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMnShtrFirstPersonCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMnShtrFirstPersonCharacter::OnStopJump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMnShtrFirstPersonCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMnShtrFirstPersonCharacter::StopRun);
}

void AMnShtrFirstPersonCharacter::ShowPauseMenu()
{
	AMnShtrGameModeBase* gameMode = Cast<AMnShtrGameModeBase>(GetWorld()->GetAuthGameMode());
	gameMode->StartShowingStartingWidget();
}

void AMnShtrFirstPersonCharacter::LoadGame()
{
	UMnShtrSaveGame* LoadGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::CreateSaveGameObject(UMnShtrSaveGame::StaticClass()));
	LoadGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	this->SetActorLocation(LoadGameInstance->Location);
	GetController()->SetControlRotation(LoadGameInstance->Rotation);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Game loaded"));
}

void AMnShtrFirstPersonCharacter::SaveGame()
{
	UMnShtrSaveGame* SaveGameInstance = Cast<UMnShtrSaveGame>(UGameplayStatics::CreateSaveGameObject(UMnShtrSaveGame::StaticClass()));
	SaveGameInstance->Location = GetActorLocation();
	SaveGameInstance->Rotation = GetController()->GetControlRotation();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Game Saved"));
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
	if (GEngine)
	{
		UE_LOG(LogTemp, Log, TEXT("bCausedByWorld = %d"), dmgType.bCausedByWorld);
		UE_LOG(LogTemp, Log, TEXT("bRadialDamageVelChange = %d"), dmgType.bRadialDamageVelChange);
		UE_LOG(LogTemp, Log, TEXT("bScaleMomentumByMass = %d"), dmgType.bScaleMomentumByMass);
		UE_LOG(LogTemp, Log, TEXT("DamageFalloff = %f"), dmgType.DamageFalloff);
		UE_LOG(LogTemp, Log, TEXT("DamageImpulse = %f"), dmgType.DamageImpulse);
		UE_LOG(LogTemp, Log, TEXT("DestructibleDamageSpreadScale = %f"), dmgType.DestructibleDamageSpreadScale);
		UE_LOG(LogTemp, Log, TEXT("DestructibleImpulse = %f"), dmgType.DestructibleImpulse);
		UE_LOG(LogTemp, Log, TEXT("Maciej Lewinski pisze logi"));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("bCausedByWorld ") + FString::FromInt(dmgType.bCausedByWorld));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("bRadialDamageVelChange ") + FString::FromInt(dmgType.bRadialDamageVelChange));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("bScaleMomentumByMass ") + FString::FromInt(dmgType.bScaleMomentumByMass));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("DamageFalloff ") + FString::SanitizeFloat(dmgType.DamageFalloff));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("DamageImpulse ") + FString::SanitizeFloat(dmgType.DamageImpulse));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("DestructibleDamageSpreadScale ") + FString::SanitizeFloat(dmgType.DestructibleDamageSpreadScale));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("DestructibleImpulse ") + FString::SanitizeFloat(dmgType.DestructibleImpulse));
	}
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
			if (UWorld* World = GetWorld())
			{
				FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
				if (LatentActionManager.FindExistingAction<FDelayAction>(this, UUID)==NULL)
				{
					FLatentActionInfo LatentActionInfo(0, UUID, TEXT("CountdownFinished"), this);
					LatentActionManager.AddNewAction(this, UUID, new FDelayAction(3, LatentActionInfo));
				}
			}
		}
	}
}
void AMnShtrFirstPersonCharacter::CountdownFinished()
{
	AMnShtrGameModeBase* gameMode = Cast<AMnShtrGameModeBase>(GetWorld()->GetAuthGameMode());
	gameMode->ChangeMenuWidget(nullptr);
}

