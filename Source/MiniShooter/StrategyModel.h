// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>

/**
 * 
 */
class MINISHOOTER_API StrategyModel
{
public:
	StrategyModel(std::string line);
	StrategyModel();
	~StrategyModel();
	
	float Move_Health;

	float Move_Distance;

	float Move_Energy;

	float Heal_Health;

	float Heal_Distance;

	float Heal_Energy;

	float Granade_Health;

	float Granade_Distance;

	float Granade_Energy;

	float Explode_Health;

	float Explode_Distance;

	float Explode_Energy;

	float Dmg;

};
