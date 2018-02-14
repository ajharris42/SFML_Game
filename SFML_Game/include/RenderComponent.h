#pragma once

#include "Graphics.h"
#include "Component.h"

class RenderComponent : public Component
{
	public:
		RenderComponent();
		~RenderComponent();

		void update(GameEntity *e) override;

	private:
		Graphics *g;
};

