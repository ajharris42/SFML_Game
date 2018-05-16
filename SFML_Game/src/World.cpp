#include "World.h"
#include "NPC.h"
#include "Camera.h"

World::World(const char *worldFile)
{
	g = Graphics::getInstance();

	MapLoader loader;

	map = loader.loadMap(worldFile);

	collisionObjects = map->getCollisionObjects();

	quad_tree = new Quadtree<GameEntity>(sf::Rect<float>(0, 0, 800, 800));
}

void World::Update(sf::Time deltaT)
{
	UpdateEntities(deltaT);
}

void World::UpdateEntities(sf::Time deltaT)
{
	bool wasThereAnUpdate;

	int entitiesSize = entities.size();
	int collisionSize = collisionObjects.size();

	std::for_each(entities.begin(), entities.end(), [&](std::shared_ptr<GameEntity> e) 
	{
		wasThereAnUpdate = e->update();

		//Loop through objects
		//TODO: This seems to have little to no affect on my framerate
		//TODO: Check performance with quadtree
		if (wasThereAnUpdate) 
		{ //If nothing changed do not check it, this is not entirely true...
			for (int j = 0; j < collisionSize; ++j) 
			{
				//Check if an entity is inside the object
				if (e->getBounds().intersects(collisionObjects[j])) 
				{
					//Move the entity back based on which way it came
					switch (e->getDirection()) {
					case 0:
						e->MoveDown();
						break;
					case 1:
						e->MoveUp();
						break;
					case 2:
						e->MoveRight();
						break;
					case 3:
						e->MoveLeft();
						break;
					default:
						break;
					}
				}
			}
		}
	});
}

//TODO: Fix camera dependencies
void World::Render(Camera c)
{
	states.texture = map->getTilesetTexture();

	//Draw layers 1 and 2

	//This seems to save only about 100 frames
	//if (c.bounds.intersects(map->getVA1().getBounds()))
	//{
		g->draw(map->getVA1(), states);

		g->draw(map->getVA2(), states);

		//Render Quads
		//For debugging purposes, extremely inefficient
		#if DEBUG_RENDER
				sf::RectangleShape recta;

				/*recta.setPosition(sf::Vector2f(p->getBounds().left, p->getBounds().top));
				recta.setSize(sf::Vector2f(64, 64));

				recta.setFillColor(sf::Color(100, 250, 50));

				g->draw(recta);*/

				for (auto i = collisionObjects.size() - 1; i != (std::vector<int>::size_type) - 1; --i) {
					sf::RectangleShape rect2;

					rect2.setPosition(sf::Vector2f(collisionObjects[i].left, collisionObjects[i].top));
					rect2.setSize(sf::Vector2f(collisionObjects[i].width, collisionObjects[i].height));

					g->draw(rect2);
				}
		#endif

		//Draw layer 3
		g->draw(map->getVA3(), states);
	//}
	
	RenderEntities(c);
}

void World::RenderEntities(Camera c)
{
	sf::RenderStates states;

	/*std::vector<Node<GameEntity>*> nodes = quad_tree->get_contained_nodes(c.bounds);
	std::for_each(nodes.begin(), nodes.end(), [&](Node<GameEntity>* node)
	{
		node->data->draw(*g->getWindow(), states);
		puts("I rendered!");
	});*/

	for (auto i = entities.size() - 1; i != std::vector<int>::size_type(-1); --i)
	{
		if (entities[i]->getBounds().intersects(c.bounds)) 
		{
			entities[i]->draw(*g->getWindow(), states);
		}
	}
}

void World::addEntity(const std::shared_ptr<GameEntity> &entity)
{
	entities.push_back(entity);

	quad_tree->insert(entity->getPosition(), entity.get());
}

World::~World()
{
	delete quad_tree;
	quad_tree = nullptr;
}