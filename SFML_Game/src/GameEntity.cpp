#include "GameEntity.h"

#include "InputComponent.h"
#include "RenderComponent.h"

GameEntity::GameEntity()
{
	position.x = 320.0f; position.y = 240.0f;
	width = 64; height = 64;

	bounds.left = position.x;
	bounds.top = position.y;
	bounds.width = width;
	bounds.height = height;

	textureBounds = sf::VertexArray(sf::Quads, 4);

	textureBounds[0].position = sf::Vector2f(position.x, position.y);
	textureBounds[0].texCoords = sf::Vector2f(0, 0);

	textureBounds[1].position = sf::Vector2f((position.x + width), position.y);
	textureBounds[1].texCoords = sf::Vector2f(width, 0);

	textureBounds[2].position = sf::Vector2f((position.x + width), (position.y + height));
	textureBounds[2].texCoords = sf::Vector2f(width, height);

	textureBounds[3].position = sf::Vector2f(position.x, (position.y + height));
	textureBounds[3].texCoords = sf::Vector2f(0, height);

	moveSpeed = 3.0f;

	direction = LEFT;
}

void GameEntity::addComponent(Component *c)
{
	components.push_back(c);
}

sf::FloatRect GameEntity::getBounds() const 
{
	return bounds;
}

void GameEntity::moveUp()
{
	position.y -= moveSpeed;
	bounds.top -= moveSpeed;

	direction = UP;
}

void GameEntity::moveDown()
{
	position.y += moveSpeed;
	bounds.top += moveSpeed;

	direction = DOWN;
}

void GameEntity::moveLeft()
{
	position.x -= moveSpeed;
	bounds.left -= moveSpeed;

	direction = LEFT;
}

void GameEntity::moveRight()
{
	position.x += moveSpeed;
	bounds.left += moveSpeed;

	direction = RIGHT;
}

GameEntity::~GameEntity()
{

}

