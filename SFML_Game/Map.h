#pragma once

#include "stdafx.h"

class Map
{
	public:
		Map(int width, int height, const sf::VertexArray &va1, const sf::VertexArray &va2, const sf::VertexArray &va3,
			const sf::Texture &tilesetTexture, const std::vector<sf::FloatRect > &collisionObjects);
		Map();
		~Map();

		sf::VertexArray getVA1() const;
		sf::VertexArray getVA2() const;
		sf::VertexArray getVA3() const;
		

		//Don't make this const
		const sf::Texture *getTilesetTexture() const;

		std::vector<sf::FloatRect > getCollisionObjects() const;
	private:
		sf::VertexArray va1, va2, va3;

		std::vector<Coordinate> tileCoordinates;
		std::vector<sf::FloatRect > collisionObjects;

		int width, height;

		sf::Texture tilesetTexture;

};

