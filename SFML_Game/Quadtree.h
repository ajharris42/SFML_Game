#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

class GameEntity;

struct Node
{
	public:
		Node(sf::Vector2<float> vect, GameEntity* data)
		{
			this->vect = vect;
			this->data = data;
		}
		
		GameEntity* data;
		
		sf::Vector2<float> vect;
};

class Quadtree
{
	private:
		const int MAX_SIZE = 5;
	
		Quadtree* north_west;
		Quadtree* north_east;
		Quadtree* south_west;
		Quadtree* south_east;
	
		sf::Rect<float> location;
		
		bool area_contains_location(sf::Rect<float> area) const;
		bool location_contains_area(sf::Rect<float> area) const;

		std::vector<Node*> points;
	public:
		explicit Quadtree(sf::Rect<float> location);
		~Quadtree();

		bool insert(Node* new_node);
		bool remove(Node* node);
		bool update(Node* node);
		std::vector<Node*> get_contained_nodes(sf::Rect<float> area) const;

};