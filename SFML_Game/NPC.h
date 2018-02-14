#pragma once

#include "GameEntity.h"

class InputComponent;
class RenderComponent;

class NPC : public GameEntity
{
	public:
		NPC(InputComponent *i, RenderComponent *g);
		~NPC();

		bool update() override;
		void render() override;

		void addComponent(Component *c) override;
};

