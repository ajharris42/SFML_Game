#include "GameEntity.h"

#include "InputComponent.h"
#include "RenderComponent.h"

GameEntity::GameEntity(const sf::Vector2f &position)
{
	setPosition(position);

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
	sf::Vector2f pos = getPosition();
	pos.y -= moveSpeed;
	setPosition(pos);

	bounds.top -= moveSpeed;

	direction = UP;
}

void GameEntity::moveDown()
{
	sf::Vector2f pos = getPosition();
	pos.y += moveSpeed;
	setPosition(pos);

	bounds.top += moveSpeed;

	direction = DOWN;
}

void GameEntity::moveLeft()
{
	
	sf::Vector2f pos = getPosition();
	pos.x -= moveSpeed;
	setPosition(pos);


	bounds.left -= moveSpeed;

	direction = LEFT;
}

void GameEntity::moveRight()
{
	sf::Vector2f pos = getPosition();
	pos.x += moveSpeed;
	setPosition(pos);

	bounds.left += moveSpeed;

	direction = RIGHT;
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

										
	states.texture = &texture;

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(textureBounds, states);
}

GameEntity::~GameEntity()
{

}

