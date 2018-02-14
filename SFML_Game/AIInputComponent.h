#pragma once

#include "InputComponent.h"

class AIInputComponent : public InputComponent
{
	public:
		AIInputComponent();
		~AIInputComponent();

		void update(GameEntity *e) override;
};

