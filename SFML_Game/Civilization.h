#pragma once

#include "stdafx.h"

class Civilization
{
	public:
		Civilization(){}
		Civilization(std::string Name);
		~Civilization();

		std::string generateRandomNation();
	private:
		std::string Nation;
		std::string Name;

		int Population;

		int foodCount, productionCount;

		int popGrowthRate;

		const static int France = 0;
		const static int Germany = 1;
		const static int England = 2;
		const static int Russia = 3;
};