// Fill out your copyright notice in the Description page of Project Settings.

#include "MnShtrFirstPersonCharacter.h"
#include "MnShtrSaveGame.h"
#include "MnShtrGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

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

//void AMnShtrFirstPersonCharacter::StopRun()
//{
//	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
//}
//
//void AMnShtrFirstPersonCharacter::StartRun()
//{
//	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
//	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
//}