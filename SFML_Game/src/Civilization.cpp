#include "Civilization.h"

Civilization::Civilization(std::string Name)
{
	Population = 1;

	foodCount = 0;
	productionCount = 1;

	this->Name = Name;	
}

std::string Civilization::generateRandomNation()
{
	int random = std::rand() % 5;

	return "Russia";
}

Civilization::~Civilization()
{

}