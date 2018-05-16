#pragma once

#include "Input.h"
#include "Component.h"

class GameEntity;

class InputComponent : public Component
{
	public:
		InputComponent() = default;
		explicit InputComponent(Input *i);
		~InputComponent();

		void update(Moveable* e) const;
		void update(GameEntity* e) override {};

	private:
		Input *i;
};
