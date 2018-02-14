#include "Map.h"

Map::Map()
{

}

Map::Map(int width, int height, const sf::VertexArray &va1, const sf::VertexArray &va2, const sf::VertexArray &va3,
	const sf::Texture &tilesetTexture, const std::vector<sf::FloatRect > &collisionObjects)
{
	this->width = width;
	this->height = height;

	this->va1 = va1;
	this->va2 = va2;
	this->va3 = va3;

	this->tilesetTexture = tilesetTexture;

	this->collisionObjects = collisionObjects;
}

sf::VertexArray Map::getVA1() const
{
	return va1;
}

sf::VertexArray Map::getVA2() const 
{
	return va2;
}

sf::VertexArray Map::getVA3() const 
{
	return va3;
}

const sf::Texture *Map::getTilesetTexture() const
{
	return &tilesetTexture;
}

std::vector<sf::FloatRect > Map::getCollisionObjects() const
{
	return collisionObjects;
}

Map::~Map() 
{

}

