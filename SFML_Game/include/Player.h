#pragma once

#include "Civilization.h"
#include "GameEntity.h"

class Player : public GameEntity
{
	public:
		Player(const sf::Vector2f &position, InputComponent* i);
		~Player();

		bool update() override;
	private:
};
