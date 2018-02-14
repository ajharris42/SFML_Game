#pragma once

#include "Civilization.h"
#include "GameEntity.h"

class Player : public GameEntity 
{
	public:
		Player();
		~Player();

		bool update() override;
		void render() override;
	private:
		void takeTurn();
};
