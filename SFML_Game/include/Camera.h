#pragma once

#include "stdafx.h"
#include "Graphics.h"

class InputComponent;

class Camera
{
	public:
		explicit Camera(InputComponent* i);

		~Camera();

		bool update();

		sf::Vector2f getPosition() const { return position; }

		float* screenX;
		float* screenY;

		sf::FloatRect bounds;

		sf::View initializeView();

		sf::View getView() const { return mainView; }

		enum Direction {UP, DOWN, LEFT, RIGHT};

		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
	private:
		sf::Vector2f position;

		sf::View mainView;

		Graphics* g;

		InputComponent* inputComponent;
};
