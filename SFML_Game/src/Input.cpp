#include "Input.h"


sf::RenderWindow* Input::window = nullptr;

bool Input::close = false;

Input::Input(sf::RenderWindow* window)
{
	this->window = window;
}

bool Input::closeWindow()
{
	//This could be written in one line, but there will likely be more checks we want to make in the future
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || close)
		return true;

	return false;
}

void Input::pollEvents() {
	sf::Event event;

	while (window->pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
				window->close();
				close = true;
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window->close();
				break;
			case sf::Event::Resized:
				window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height))); //Resize Render region
				break;
			default:
				break;
		}
	}
}

//I don't like how much duplication there is in this, but I have yet to find a better solution
EntityCommand* Input::getEntityInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		return new MoveCommand(GameEntity::UP);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		return new MoveCommand(GameEntity::DOWN);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		return new MoveCommand(GameEntity::LEFT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		return new MoveCommand(GameEntity::RIGHT);

	return nullptr;
}

CameraCommand* Input::getCameraInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		return new MoveCommand(GameEntity::UP);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		return new MoveCommand(GameEntity::DOWN);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return new MoveCommand(GameEntity::LEFT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		return new MoveCommand(GameEntity::RIGHT);

	return nullptr;
}

Input::~Input()
{

}