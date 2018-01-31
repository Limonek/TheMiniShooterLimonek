// Fill out your copyright notice in the Description page of Project Settings.
#include "AIBasicEnemyCtr.h"
#include "MiniShooter.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>  
#include <algorithm>
#include <random>
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
	std::ifstream infile("C:/botFile.txt");
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
	int r = (int)(((double)rand() / (RAND_MAX)) * (ProperStrategys.size()-1));
	std::random_device rd;
	std::mt19937 gen(rd());

	//standard deviation
	float Explode_Distance_StdDev = 0;
	for (int n = 0; n < ProperStrategys.size(); n++)
	{
		Explode_Distance_StdDev += (ProperStrategys[n].Explode_Distance - ProperStrategys[r].Explode_Distance) * (ProperStrategys[n].Explode_Distance - ProperStrategys[r].Explode_Distance);
	}
	Explode_Distance_StdDev /= ProperStrategys.size();
	Explode_Distance_StdDev = sqrt(Explode_Distance_StdDev);
	if (ProperStrategys.size() < 3)
		Explode_Distance_StdDev = 0.5;
	std::normal_distribution<float> d(ProperStrategys[r].Explode_Distance, Explode_Distance_StdDev);
	Strategy.Explode_Distance = d(gen);
	if(Strategy.Explode_Distance > 1)
		Strategy.Explode_Distance = 1 - Strategy.Explode_Distance;


	float Explode_Energy_StdDev = 0;
	for (int n = 0; n < ProperStrategys.size(); n++)
	{
		Explode_Energy_StdDev += (ProperStrategys[n].Explode_Energy - ProperStrategys[r].Explode_Energy) * (ProperStrategys[n].Explode_Energy - ProperStrategys[r].Explode_Energy);
	}
	Explode_Energy_StdDev /= ProperStrategys.size();
	Explode_Energy_StdDev = sqrt(Explode_Energy_StdDev);
	if (ProperStrategys.size() < 3)
		Explode_Energy_StdDev = 0.5;
	std::normal_distribution<float> d1(ProperStrategys[r].Explode_Energy, Explode_Energy_StdDev);
	Strategy.Explode_Energy = d1(gen);
	if (Strategy.Explode_Energy > 1)
		Strategy.Explode_Energy = 1 - Strategy.Explode_Energy;



	float Explode_Health_StdDev = 0;
	for (int n = 0; n < ProperStrategys.size(); n++)
	{
		Explode_Health_StdDev += (ProperStrategys[n].Explode_Health - ProperStrategys[r].Explode_Health) * (ProperStrategys[n].Explode_Health - ProperStrategys[r].Explode_Health);
	}
	Explode_Health_StdDev /= ProperStrategys.size();
	Explode_Health_StdDev = sqrt(Explode_Health_StdDev);
	if (ProperStrategys.size() < 3)
		Explode_Health_StdDev = 0.5;
	std::normal_distribution<float> d2(ProperStrategys[r].Explode_Health, Explode_Health_StdDev);
	Strategy.Explode_Health = d2(gen);
	if (Strategy.Explode_Health > 1)
		Strategy.Explode_Health = 1 - Strategy.Explode_Health;



	float Granade_Distance_StdDev = 0;
	for (int n = 0; n < ProperStrategys.size(); n++)
	{
		Granade_Distance_StdDev += (ProperStrategys[n].Granade_Distance - ProperStrategys[r].Granade_Distance) * (ProperStrategys[n].Granade_Distance - ProperStrategys[r].Granade_Distance);
	}
	Granade_Distance_StdDev /= ProperStrategys.size();
	Granade_Distance_StdDev = sqrt(Granade_Distance_StdDev);
	if (ProperStrategys.size() < 3)
		Granade_Distance_StdDev = 0.5;
	std::normal_distribution<float> d3(ProperStrategys[r].Granade_Distance, Granade_Distance_StdDev);
	Strategy.Granade_Distance = d3(gen);
	if (Strategy.Granade_Distance > 1)
		Strategy.Granade_Distance = 1 - Strategy.Granade_Distance;



	float Granade_Energy_StdDev = 0;
	for (int n = 0; n < ProperStrategys.size(); n++)
	{
		Granade_Energy_StdDev += (ProperStrategys[n].Granade_Energy - ProperStrategys[r].Granade_Energy) * (ProperStrategys[n].Granade_Energy - ProperStrategys[r].Granade_Energy);
	}
	Granade_Energy_StdDev /= ProperStrategys.size();
	Granade_Energy_StdDev = sqrt(Granade_Energy_StdDev);
	if (ProperStrategys.size() < 3)
		Granade_Energy_StdDev = 0.5;
	std::normal_distribution<float> d4(ProperStrategys[r].Granade_Energy, Granade_Energy_StdDev);
	Strategy.Granade_Energy = d4(gen);
	if (Strategy.Granade_Energy > 1)
		Strategy.Granade_Energy = 1 - Strategy.Granade_Energy;



	float Granade_Health_StdDev = 0;
	for (int n = 0; n < ProperStrategys.size(); n++)
	{
		Granade_Health_StdDev += (ProperStrategys[n].Granade_Health - ProperStrategys[r].Granade_Health) * (ProperStrategys[n].Granade_Health - ProperStrategys[r].Granade_Health);
	}
	Granade_Health_StdDev /= ProperStrategys.size();
	Granade_Health_StdDev = sqrt(Granade_Health_StdDev);
	if (ProperStrategys.size() < 3)
		Granade_Health_StdDev = 0.5;
	std::normal_distribution<float> d5(ProperStrategys[r].Granade_Health, Granade_Health_StdDev);
	Strategy.Granade_Health = d5(gen);
	if (Strategy.Granade_Health > 1)
		Strategy.Granade_Health = 1 - Strategy.Granade_Health;



	float Heal_Distance_StdDev = 0;
	for (int n = 0; n < ProperStrategys.size(); n++)
	{
		Heal_Distance_StdDev += (ProperStrategys[n].Heal_Distance - ProperStrategys[r].Heal_Distance) * (ProperStrategys[n].Heal_Distance - ProperStrategys[r].Heal_Distance);
	}
	Heal_Distance_StdDev /= ProperStrategys.size();
	Heal_Distance_StdDev = sqrt(Heal_Distance_StdDev);
	if (ProperStrategys.size() < 3)
		Heal_Distance_StdDev = 0.5;
	std::normal_distribution<float> d6(ProperStrategys[r].Heal_Distance, Heal_Distance_StdDev);
	Strategy.Heal_Distance = d6(gen);
	if (Strategy.Heal_Distance > 1)
		Strategy.Heal_Distance = 1 - Strategy.Heal_Distance;



	float Heal_Energy_StdDev = 0;
	for (int n = 0; n < ProperStrategys.size(); n++)
	{
		Heal_Energy_StdDev += (ProperStrategys[n].Heal_Energy - ProperStrategys[r].Heal_Energy) * (ProperStrategys[n].Heal_Energy - ProperStrategys[r].Heal_Energy);
	}
	Heal_Energy_StdDev /= ProperStrategys.size();
	Heal_Energy_StdDev = sqrt(Heal_Energy_StdDev);
	if (ProperStrategys.size() < 3)
		Heal_Energy_StdDev = 0.5;
	std::normal_distribution<float> d7(ProperStrategys[r].Heal_Energy, Heal_Energy_StdDev);
	Strategy.Heal_Energy = d7(gen);
	if (Strategy.Heal_Energy > 1)
		Strategy.Heal_Energy = 1 - Strategy.Heal_Energy;



	float Heal_Health_StdDev = 0;
	for (int n = 0; n < ProperStrategys.size(); n++)
	{
		Heal_Health_StdDev += (ProperStrategys[n].Heal_Health - ProperStrategys[r].Heal_Health) * (ProperStrategys[n].Heal_Health - ProperStrategys[r].Heal_Health);
	}
	Heal_Health_StdDev /= ProperStrategys.size();
	Heal_Health_StdDev = sqrt(Heal_Health_StdDev);
	if (ProperStrategys.size() < 3)
		Heal_Health_StdDev = 0.5;
	std::normal_distribution<float> d8(ProperStrategys[r].Heal_Health, Heal_Health_StdDev);
	Strategy.Heal_Health = d8(gen);
	if (Strategy.Heal_Health > 1)
		Strategy.Heal_Health = 1 - Strategy.Heal_Health;



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
