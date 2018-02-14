#pragma once

#include "Input.h"
#include "Component.h"

class GameEntity;

class InputComponent : public Component
{
	public:
		InputComponent(){}
		explicit InputComponent(Input *i);
		~InputComponent();

		void update(GameEntity *e) override;

		//I don't like this fix, but we'll come back to it later
		void update(Camera *c) const;

	private:
		Input *i;
};
