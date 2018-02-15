#include "QuadTree.h"
#include <iostream>

Quadtree::Quadtree(const sf::Rect<float> &location)
{
	this->location = location;

	north_west = nullptr;
	north_east = nullptr;
	south_east = nullptr;
	south_west = nullptr;
}

bool Quadtree::area_contains_location(const sf::Rect<float> &area) const
{
	return (location.left >= area.left && location.top >= area.top &&
		    location.left + location.width <= area.left + area.width &&
			location.top + location.height <= area.top + area.height
		   );
}

bool Quadtree::location_contains_area(const sf::Rect<float> &area) const
{
	return (location.left <= area.left && location.top <= area.top &&
			location.left + location.width >= area.left + area.width &&
			location.top + location.height >= area.top + area.height
		   );
}

bool Quadtree::insert(Node* new_node)
{
	if(!location.contains(new_node->vect))
	{
		return false;
	}
	
	if (points.size() < MAX_SIZE)
	{
		points.push_back(new_node);

		return true;
	}

	sf::Rect<float> tmp(location);
	tmp.width /= 2.0f;
	tmp.height /= 2.0f;
	
	Quadtree* curr = nullptr;

	if (tmp.contains(new_node->vect))
	{
		if (north_west != nullptr)
		{
			return north_west->insert(new_node);
		}

		north_west = new Quadtree(tmp);

		curr = north_west;
	}

	tmp.left += tmp.width;
	if (tmp.contains(new_node->vect))
	{
		if (north_east != nullptr)
		{
			return north_east->insert(new_node);
		}

		north_east = new Quadtree(tmp);
			
		curr = north_east;
	}
	
	tmp.top += tmp.height;
	if (tmp.contains(new_node->vect))
	{
		if (south_east != nullptr)
		{
			return south_east->insert(new_node);
		}

		south_east = new Quadtree(tmp);
			
		curr = south_east;
	}
	
	tmp.left -= tmp.width;
	if (tmp.contains(new_node->vect))
	{
		if (south_west != nullptr)
		{
			return south_west->insert(new_node);
		}

		south_west = new Quadtree(tmp);
						
		curr = south_west;
	}

	for (std::size_t i = 0; i < points.size(); ++i)
	{
		if (curr->location.contains(points[i]->vect))
		{
			curr->insert(points[i]);

			points.erase(points.begin() + i);

			--i;
		}
	}

	return curr->insert(new_node);
}

bool Quadtree::remove(Node* node)
{

	if (north_west != nullptr)
	{
		north_west->remove(node);

		if (north_west->get_contained_nodes(north_west->location).empty())
		{
			delete north_west;
			north_west = nullptr;
		}
	}

	if (north_east != nullptr)
	{
		const bool success = north_east->remove(node);

		if (north_east->get_contained_nodes(north_east->location).empty())
		{
			delete north_east;
			north_east = nullptr;
		}

		return success;
	}

	if (south_east != nullptr)
	{
		const bool success = south_east->remove(node);

		if (south_east->get_contained_nodes(south_east->location).empty())
		{
			delete south_east;
			south_east = nullptr;
		}

		return success;
	}

	if (south_west != nullptr)
	{
		const bool success = south_west->remove(node);

		if (south_west->get_contained_nodes(south_west->location).empty())
		{
			delete south_west;
			south_west = nullptr;
		}

		return success;
	}

	const auto elem = std::find(points.begin(), points.end(), node);
	if (elem != points.end())
	{
		points.erase(elem);

		return true;
	}

	return false;
}

bool Quadtree::update(Node* node)
{
	const auto elem = std::find(points.begin(), points.end(), node);
	if (elem != points.end())
	{
		if (!location.contains(node->vect))
		{
			points.erase(elem);

			return true;
		}

		*elem = node;
	}

	if (north_west != nullptr)
	{
		if (north_west->update(node))
		{
			return insert(node);
		}
	}

	if (north_east != nullptr)
	{
		if (north_east->update(node))
		{
			return insert(node);
		}
	}

	if (south_east != nullptr)
	{
		if (south_east->update(node))
		{
			return insert(node);
		}
	}

	if (south_west != nullptr)
	{
		if (south_west->update(node))
		{
			return insert(node);
		}
	}

	return false;
}

std::vector<Node*> Quadtree::get_contained_nodes(const sf::Rect<float> &area) const
{
	std::vector<Node*> nodes;

	if (location.intersects(area))
	{
		std::for_each(points.begin(), points.end(), [&](Node* node)
		{
			if (area.contains(node->vect))
			{
				nodes.push_back(node);
			}
		});
	}

	if (north_west != nullptr)
	{
		auto values = north_west->get_contained_nodes(area);
			
		nodes.reserve(values.size());
		nodes.insert(nodes.end(), values.begin(), values.end());
	}
	
	if (north_east != nullptr)
	{
		auto values = north_east->get_contained_nodes(area);
			
		nodes.reserve(values.size());
		nodes.insert(nodes.end(), values.begin(), values.end());
	}
	
	if (south_east != nullptr)
	{
		auto values = south_east->get_contained_nodes(area);
			
		nodes.reserve(values.size());
		nodes.insert(nodes.end(), values.begin(), values.end());
	}
	
	if (south_west != nullptr)
	{
		auto values = south_west->get_contained_nodes(area);
			
		nodes.reserve(values.size());
		nodes.insert(nodes.end(), values.begin(), values.end());
	}
	
	return nodes;
}

Quadtree::~Quadtree()
{
	delete north_west;
	delete north_east;
	delete south_west;
	delete south_east;
}