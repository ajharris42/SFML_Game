#pragma once

#include "Civilization.h"
#include "GameEntity.h"

class Player : public GameEntity 
{
	public:
		Player(const sf::Vector2f &position);
		~Player();

		bool update() override;
	private:
};
