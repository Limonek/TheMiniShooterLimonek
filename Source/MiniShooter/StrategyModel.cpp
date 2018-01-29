// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyModel.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

StrategyModel::StrategyModel()
{
	Move_Health = (float)rand() / (RAND_MAX + 1.0);
	Move_Distance = (float)rand() / (RAND_MAX + 1.0);
	Move_Energy = (float)rand() / (RAND_MAX + 1.0);
	Heal_Health = (float)rand() / (RAND_MAX + 1.0);
	Heal_Distance = (float)rand() / (RAND_MAX + 1.0);
	Heal_Energy = (float)rand() / (RAND_MAX + 1.0);
	Granade_Health = (float)rand() / (RAND_MAX + 1.0);
	Granade_Distance = (float)rand() / (RAND_MAX + 1.0);
	Granade_Energy = (float)rand() / (RAND_MAX + 1.0);
	Explode_Health = (float)rand() / (RAND_MAX + 1.0);
	Explode_Distance = (float)rand() / (RAND_MAX + 1.0);
	Explode_Energy = (float)rand() / (RAND_MAX + 1.0);
	Dmg = 0;
}
StrategyModel::StrategyModel(std::string line)
{
	std::stringstream test(line);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(test, segment, '#'))
	{
		seglist.push_back(segment);
	}

	Move_Health = strtof((seglist[0]).c_str(), 0);
	Move_Distance = strtof((seglist[2]).c_str(), 0);
	Move_Energy = strtof((seglist[4]).c_str(), 0);
	Heal_Health = strtof((seglist[6]).c_str(), 0);
	Heal_Distance = strtof((seglist[8]).c_str(), 0);
	Heal_Energy = strtof((seglist[10]).c_str(), 0);
	Granade_Health = strtof((seglist[12]).c_str(), 0);
	Granade_Distance = strtof((seglist[14]).c_str(), 0);
	Granade_Energy = strtof((seglist[16]).c_str(), 0);
	Explode_Health = strtof((seglist[18]).c_str(), 0);
	Explode_Distance = strtof((seglist[20]).c_str(), 0);
	Explode_Energy = strtof((seglist[22]).c_str(), 0);
	Dmg = strtof((seglist[24]).c_str(), 0);
}

StrategyModel::~StrategyModel()
{
}
