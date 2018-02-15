#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <iostream>

template <class T>
class Node
{
	public:
		Node(sf::Vector2f vect, T* data)
		{
			this->vect = vect;
			this->data = data;
		}
		
		T* data;
		sf::Vector2f vect;
};

template <class T>
class Quadtree
{
	private:
		const std::size_t MAX_SIZE = 5;
	
		Quadtree<T>* north_west;
		Quadtree<T>* north_east;
		Quadtree<T>* south_west;
		Quadtree<T>* south_east;
	
		sf::Rect<float> location;
		
		bool area_contains_location(const sf::Rect<float> &area) const;
		bool location_contains_area(const sf::Rect<float> &area) const;

		std::vector<Node<T>*> points;
	public:
		explicit Quadtree(const sf::Rect<float> &location);
		~Quadtree();

		bool insert(const sf::Vector2f &vect, T* new_val);
		bool remove(T* node);
		bool update(T* node);
		std::vector<Node<T>*> get_contained_nodes(const sf::Rect<float> &area) const;

};

template <class T>
Quadtree<T>::Quadtree(const sf::Rect<float> &location)
{
	this->location = location;

	north_west = nullptr;
	north_east = nullptr;
	south_east = nullptr;
	south_west = nullptr;
}

template <class T>
bool Quadtree<T>::area_contains_location(const sf::Rect<float> &area) const
{
	return (location.left >= area.left && location.top >= area.top &&
		location.left + location.width <= area.left + area.width &&
		location.top + location.height <= area.top + area.height
		);
}

template <class T>
bool Quadtree<T>::location_contains_area(const sf::Rect<float> &area) const
{
	return (location.left <= area.left && location.top <= area.top &&
		location.left + location.width >= area.left + area.width &&
		location.top + location.height >= area.top + area.height
		);
}

template <class T>
bool Quadtree<T>::insert(const sf::Vector2f &vect, T* new_val)
{
	if (!location.contains(vect))
	{
		return false;
	}

	if (points.size() < MAX_SIZE)
	{
		Node<T>* new_node = new Node<T>(vect, new_val);

		points.push_back(new_node);

		return true;
	}

	sf::Rect<float> tmp(location);
	tmp.width /= 2.0f;
	tmp.height /= 2.0f;

	Quadtree* curr = nullptr;

	if (tmp.contains(vect))
	{
		if (north_west != nullptr)
		{
			return north_west->insert(vect, new_val);
		}

		north_west = new Quadtree(tmp);

		curr = north_west;
	}

	tmp.left += tmp.width;
	if (tmp.contains(vect))
	{
		if (north_east != nullptr)
		{
			return north_east->insert(vect, new_val);
		}

		north_east = new Quadtree(tmp);

		curr = north_east;
	}

	tmp.top += tmp.height;
	if (tmp.contains(vect))
	{
		if (south_east != nullptr)
		{
			return south_east->insert(vect, new_val);
		}

		south_east = new Quadtree(tmp);

		curr = south_east;
	}

	tmp.left -= tmp.width;
	if (tmp.contains(vect))
	{
		if (south_west != nullptr)
		{
			return south_west->insert(vect, new_val);
		}

		south_west = new Quadtree(tmp);

		curr = south_west;
	}

	for (std::size_t i = 0; i < points.size(); ++i)
	{
		if (curr->location.contains(points[i]->vect))
		{
			curr->insert(points[i]->vect, points[i]->data);

			points.erase(points.begin() + i);

			--i;
		}
	}

	return curr->insert(vect, new_val);
}

template <class T>
bool Quadtree<T>::remove(T* node)
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

	const auto elem = std::find_if(points.begin(), points.end(), [&](Node<T>* val)
	{
		return val->data == node;
	});

	if (elem != points.end())
	{
		points.erase(elem);

		return true;
	}

	return false;
}

template <class T>
bool Quadtree<T>::update(T* node)
{
	const auto elem = std::find_if(points.begin(), points.end(), [&](Node<T>* val)
	{
		return val->data == node;
	});

	if (elem != points.end())
	{
		if (!location.contains(elem->vect))
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

template <class T>
std::vector<Node<T>*> Quadtree<T>::get_contained_nodes(const sf::Rect<float> &area) const
{
	std::vector<Node<T>*> nodes;

	if (location.intersects(area))
	{
		std::for_each(points.begin(), points.end(), [&](Node<T>* node)
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

template <class T>
Quadtree<T>::~Quadtree()
{
	delete north_west;
	delete north_east;
	delete south_west;
	delete south_east;
}