#include "Game.h"
#include "AIInputComponent.h"
#include "Player.h"
#include "Camera.h"
#include "NPC.h"
#include "InputComponent.h"
#include "RenderComponent.h"


//Graphics *Game::g = Graphics::getInstance();

Game::Game() 
{
	g = Graphics::getInstance();

	i = std::make_unique<Input>(g->getWindow());
	p = std::make_shared<Player>(sf::Vector2f(320, 320));

	running = true;

	timeSinceLastUpdate = sf::Time::Zero;
}

void Game::work()
{
	World world("data/cheatMapv2.tmx");
	//World world("data/test16Map.tmx", "gfx/test16sheet.png");

	//world.setPlayer(p);

	std::shared_ptr<InputComponent> input = std::make_shared<InputComponent>(i.get());
	AIInputComponent aiController;

	std::shared_ptr<RenderComponent> r1 = std::make_shared<RenderComponent>();

	//This is temporary, components should be added elsewhere. Also should use smart pointers
	std::shared_ptr<GameEntity> e = std::make_shared<NPC>(sf::Vector2f(400, 400), &aiController);
	std::shared_ptr<GameEntity> j = std::make_shared<NPC>(sf::Vector2f(200, 200), input.get());

	e->setId(0);
	j->setId(1);

	world.addEntity(p);
	world.addEntity(e);
	world.addEntity(j);

	Camera camera = Camera(input.get());

	while(running)
	{
		Input::pollEvents();

		if (Input::closeWindow())  //Check if we should close the window
		{
			running = false; //Slightly redundent
			break;
		}

		sf::Time elapsedTime = clock.restart();

		timeSinceLastUpdate += elapsedTime;

		//Fixed time loop, not great but for testing purposes it works
		while (timeSinceLastUpdate > timePerFrame) 
		{
			timeSinceLastUpdate -= timePerFrame;

			camera.update(); //Updates the view based on the Camera shift

			world.Update(timePerFrame);
			//mm.update(timePerFrame); //Animates Tiles
		}

		g->clearWindow(); //Clear the buffer

		world.Render(camera);

		g->updateWindow(); //Show the screen
	}
}

Game::~Game()
{

}