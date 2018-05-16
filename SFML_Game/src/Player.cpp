#include "Player.h"
#include "InputComponent.h"

Player::Player(const sf::Vector2f &position, InputComponent* i) : GameEntity(position)
{
	setPosition(position);

	inputComponent = i;

	//position.x = 320; 
	//position.y = 240;
	width = 64;
	height = 64;

	moveSpeed = 120;

	texture.loadFromFile("gfx/player.png");

	/*bounds[0].color = sf::Color::Red;
	bounds[1].color = sf::Color::Blue;
	bounds[2].color = sf::Color::Green;
	bounds[3].color = sf::Color::Cyan;

	textureBounds = getBounds();*/

	direction = 0;
}

bool Player::update()
{
	if (inputComponent != nullptr)
	{
		inputComponent->update(this);

		const sf::Vector2f pos = getPosition();

		//Update where the texture should be applied
		textureBounds[0].position = sf::Vector2f(pos.x, pos.y);
		textureBounds[1].position = sf::Vector2f((pos.x + width), pos.y);
		textureBounds[2].position = sf::Vector2f((pos.x + width), (pos.y + height));
		textureBounds[3].position = sf::Vector2f(pos.x, (pos.y + height));

		return true;
	}

	return false;
}

Player::~Player()
{

}