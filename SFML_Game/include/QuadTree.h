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

		Node(sf::Vector2<float> vect, int test_data)
		{
			this->vect = vect;
			this->test_data = test_data;
		}
		
		GameEntity* data;
		int test_data;
		
		sf::Vector2<float> vect;
};

class Quadtree
{
	private:
		const std::size_t MAX_SIZE = 5;
	
		Quadtree* north_west;
		Quadtree* north_east;
		Quadtree* south_west;
		Quadtree* south_east;
	
		sf::Rect<float> location;
		
		bool area_contains_location(const sf::Rect<float> &area) const;
		bool location_contains_area(const sf::Rect<float> &area) const;

		std::vector<Node*> points;
	public:
		explicit Quadtree(const sf::Rect<float> &location);
		~Quadtree();

		bool insert(Node* new_node);
		bool remove(Node* node);
		bool update(Node* node);
		std::vector<Node*> get_contained_nodes(const sf::Rect<float> &area) const;

};