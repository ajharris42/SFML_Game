#pragma once

#include "MapLoader.h"
#include "Graphics.h"
#include "Player.h"
#include "Quadtree.h"

class Camera;

class World
{
	public:
		explicit World(const char *worldFile);
		~World();

		void Update(sf::Time deltaT);
		void UpdateEntities(sf::Time deltaT);

		void Render(Camera c);
		void RenderEntities(Camera c);

		sf::RenderStates states;

		//void setPlayer(std::shared_ptr<Player> p) { this->p = p; addEntity(p); }

		void addEntity(const std::shared_ptr<GameEntity> &entity);
	private:
		Graphics* g;
		Quadtree<GameEntity>* quad_tree;

		std::shared_ptr<Map> map;
		std::shared_ptr<Player> p;

		std::vector<std::shared_ptr<GameEntity> > entities;
		std::vector<sf::FloatRect > collisionObjects;
};

