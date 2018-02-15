#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Component;
class InputComponent;
class RenderComponent;

class GameEntity
{
	public:
		GameEntity();
		virtual ~GameEntity();

		virtual bool update() = 0;
		virtual void render() = 0;

		sf::FloatRect getBounds() const;

		float getX() const { return position.x; }
		float getY() const { return position.y; }
		float getWidth() const { return width; }
		float getHeight() const { return height; }
		int getId() const { return id; }
		void setId(int id) { this->id = id; }
		sf::Vector2f getPosition() const { return position; }

		virtual void addComponent(Component *c);

		enum Direction { UP, DOWN, LEFT, RIGHT };

		virtual void moveUp();
		virtual void moveDown();
		virtual void moveLeft();
		virtual void moveRight();

		sf::RenderStates getRenderStates() const { return renderStates; }
		sf::VertexArray getTextureBounds() const { return textureBounds; }

		int getDirection() const { return direction; }
	protected:
		std::vector<Component *> components;

		sf::Texture texture;
		sf::FloatRect bounds;

		sf::Vector2f position;

		float width, height;
		float moveSpeed;

		sf::VertexArray textureBounds;

		int direction;
		int id;

		sf::RenderStates renderStates;

		InputComponent *inputComponent;
		RenderComponent *renderComponent;
};

