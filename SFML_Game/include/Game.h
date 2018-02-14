#pragma once

#include "Input.h"
#include "World.h"

class Player;
class Graphics;

//Main class and will serve as a mediator between things

class Game
{
	public:
		Game();
		~Game();

		void work();
	private:
		std::unique_ptr<Input> i;
		Graphics *g;

		std::shared_ptr<Player> p;

		sf::Clock clock;
		sf::Time timeSinceLastUpdate;

		float time;
		sf::Time deltaTime;
		float currentTime;

		bool running;
};