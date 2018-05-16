#pragma once

#include "stdafx.h"
#include "Graphics.h"
#include "Moveable.h"

class InputComponent;

class Camera : Moveable
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

		void MoveUp() override;
		void MoveDown() override;
		void MoveLeft() override;
		void MoveRight() override;
	private:
		sf::Vector2f position;

		sf::View mainView;

		Graphics* g;

		InputComponent* inputComponent;
};
