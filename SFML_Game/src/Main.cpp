#include "Game.h"

#include "Quadtree.h"
int main(int argc, char *argv[])
{
	std::srand(std::time(nullptr));

	//Game g;

	//g.work();

	Quadtree<int> tree(sf::Rect<float>(0, 0, 10, 10));

	int* node = new int(3);
	int* node6 = new int(6);

	tree.insert(sf::Vector2f(1, 1), new int(1));
	tree.insert(sf::Vector2f(4, 1), new int(2));
	tree.insert(sf::Vector2f(7, 2), node);
	tree.insert(sf::Vector2f(6, 6), new int(4));
	tree.insert(sf::Vector2f(2, 7), new int(5));
	tree.insert(sf::Vector2f(2, 2), node6);

	puts("After Insertion:");
	auto values = tree.get_contained_nodes(sf::Rect<float>(0, 0, 10, 10));
	std::for_each(values.begin(), values.end(), [&](Node<int>* val)
	{
		std::cout << "X: " << val->vect.x << " Y: " << val->vect.y << " Data: " << *val->data << "\n";
	});

	//tree.remove(&node);
	//tree.remove(&node6);

	puts("\nAfter Update:");

	tree.update(sf::Vector2f(7, 3), node6);

	values = tree.get_contained_nodes(sf::Rect<float>(0, 0, 10, 10));
	std::for_each(values.begin(), values.end(), [&](Node<int>* val)
	{
		std::cout << "X: " << val->vect.x << " Y: " << val->vect.y << " Data: " << *val->data << "\n";
	});

	std::cin.get();

	if(DEBUG_MODE)
		_CrtDumpMemoryLeaks();

	return 0;
}