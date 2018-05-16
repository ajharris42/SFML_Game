#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Moveable.h"

class Component;
class InputComponent;

class GameEntity : public sf::Drawable, public sf::Transformable, public Moveable
{
	public:
		explicit GameEntity(const sf::Vector2f &position);
		virtual ~GameEntity() = default;

		virtual bool update() = 0;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		sf::FloatRect getBounds() const;

		float getWidth() const { return width; }
		float getHeight() const { return height; }
		int getId() const { return id; }
		void setId(int id) { this->id = id; }

		virtual void addComponent(Component *c);

		enum Direction { UP, DOWN, LEFT, RIGHT };

		void MoveUp() override;
		void MoveDown() override;
		void MoveLeft() override;
		void MoveRight() override;

		sf::RenderStates getRenderStates() const { return renderStates; }
		sf::VertexArray getTextureBounds() const { return textureBounds; }

		int getDirection() const { return direction; }
	protected:
		std::vector<Component *> components;

		sf::Texture texture;
		sf::FloatRect bounds;

		float width, height;
		float moveSpeed;

		sf::VertexArray textureBounds;

		int direction;
		int id;

		sf::RenderStates renderStates;

		InputComponent* inputComponent;
};

