// Fill out your copyright notice in the Description page of Project Settings.
#include "AIBasicEnemyCtr.h"
#include "MiniShooter.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>  
#include <algorithm>
#include "StrategyModel.h"
#include "MiniCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoard/BlackboardKeyAllTypes.h"
#include "AIBasicEnemyChar.h"
#include "AIBasicEnemyCtr.h"

#define FIRE 1
#define GRANADE 2
#define HEAL 3
#define EXPLODE 4
const char seperator = '#';
AAIBasicEnemyCtr::AAIBasicEnemyCtr()
{
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	BehaviourComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));

	LoadData();
}

void AAIBasicEnemyCtr::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	AAIBasicEnemyChar *Char = Cast<AAIBasicEnemyChar>(InPawn);
	Bot = Char;

	if (Char && Char->BotBehavior)
	{
		BlackBoardComp->InitializeBlackboard(*Char->BotBehavior->BlackboardAsset);

		EnemyKeyID = BlackBoardComp->GetKeyID("Target");

		BehaviourComp->StartTree(*Char->BotBehavior);
	}
}
void AAIBasicEnemyCtr::SaveData(float Dmg)
{
	std::ofstream outfile;
	outfile.open("X:/botFile.txt", std::ios_base::app);
	outfile << Strategy.Move_Health << seperator
		<< Strategy.Move_Distance << seperator
		<< Strategy.Move_Energy << seperator

		<< Strategy.Heal_Health << seperator
		<< Strategy.Heal_Distance << seperator
		<< Strategy.Heal_Energy << seperator

		<< Strategy.Granade_Health << seperator
		<< Strategy.Granade_Distance << seperator
		<< Strategy.Granade_Energy << seperator

		<< Strategy.Explode_Health << seperator
		<< Strategy.Explode_Distance << seperator
		<< Strategy.Explode_Energy << seperator

		<< Dmg << std::endl;

	outfile.close();
}

int AAIBasicEnemyCtr::EvaluateData()
{
	AMiniCharacter *Enemy = Cast<AMiniCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (Enemy != NULL) {
		const FVector ActorLocation = Bot->GetActorLocation();
		const FVector EnemyLocation = Enemy->GetActorLocation();
		float dist = (ActorLocation - EnemyLocation).Size();
		return GetStrategy(dist, Bot->GetEnergy(), Bot->GetHealth());
	}

	return -1;
}


void AAIBasicEnemyCtr::LoadData()
{
	std::ifstream infile("X:/botFile.txt");
	std::vector<StrategyModel> Strategys;
	std::vector<StrategyModel> ProperStrategys;
	std::string line;
	while (std::getline(infile, line))
	{
		Strategys.push_back(StrategyModel(line));
	}
	if (Strategys.size() == 0) 
	{
		Strategy = StrategyModel();
		return;
	}
	float MeanDmg=0;
	for (int i = 0; i < Strategys.size(); i++)
		MeanDmg += Strategys[i].Dmg;
	MeanDmg /= Strategys.size();
	for (int i = 0; i < Strategys.size(); i++)
		if (Strategys[i].Dmg > MeanDmg)
			ProperStrategys.push_back(Strategys[i]);

}

int AAIBasicEnemyCtr::GetStrategy(float dist, float energy, float hp)
{
	float HealthScore = Strategy.Heal_Distance * dist/10 + Strategy.Heal_Energy * energy + Strategy.Heal_Health * hp;
	float ExplodeScore = Strategy.Explode_Distance * dist / 10 + Strategy.Explode_Energy * energy + Strategy.Explode_Health * hp;
	float GranadeScore = Strategy.Granade_Distance * dist / 10 + Strategy.Granade_Energy * energy + Strategy.Granade_Health * hp;
	float MoveScore = Strategy.Move_Distance * dist / 10 + Strategy.Move_Energy * energy + Strategy.Move_Health * hp;
	float max = std::max(HealthScore, std::max(ExplodeScore, std::max(GranadeScore, MoveScore)));
	if (max == MoveScore)
		return FIRE;
	if (max == HealthScore)
		return HEAL;
	if (max == ExplodeScore)
		return EXPLODE;
	if (max == GranadeScore)
		return GRANADE;
	return -1;
}
