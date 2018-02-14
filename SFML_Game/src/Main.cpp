#include "Game.h"

#include "QuadTree.h"

int main(int argc, char *argv[])
{
	std::srand(std::time(nullptr));

	//Game g;

	//g.work();

	Quadtree tree(sf::Rect<float>(0, 0, 10, 10));

	Node node(sf::Vector2<float>(7, 2), 3);
	Node node6(sf::Vector2<float>(2, 2), 6);
	tree.insert(new Node(sf::Vector2<float>(1, 1), 1));
	tree.insert(new Node(sf::Vector2<float>(4, 1), 2));
	tree.insert(&node);
	tree.insert(new Node(sf::Vector2<float>(6, 6), 4));
	tree.insert(new Node(sf::Vector2<float>(2, 7), 5));
	tree.insert(&node6);

	puts("After Insertion:");
	auto values = tree.get_contained_nodes(sf::Rect<float>(0, 0, 10, 10));
	std::for_each(values.begin(), values.end(), [&](Node* val)
	{
		std::cout << "X: " << val->vect.x << " Y: " << val->vect.y << " Data: " << val->test_data << "\n";
	});

	//tree.remove(&node);
	//tree.remove(&node6);

	puts("\nAfter Update:");

	node6.vect = sf::Vector2<float>(7, 2);
	tree.update(&node);

	values = tree.get_contained_nodes(sf::Rect<float>(0, 0, 10, 10));
	std::for_each(values.begin(), values.end(), [&](Node* val)
	{
		std::cout << "X: " << val->vect.x << " Y: " << val->vect.y << " Data: " << val->test_data << "\n";
	});

	std::cin.get();

	if(DEBUG_MODE)
		_CrtDumpMemoryLeaks();

	return 0;
}