#pragma once

#include "GameEntity.h"

class InputComponent;

class NPC : public GameEntity
{
	public:
		NPC(const sf::Vector2f &position, InputComponent* i);
		~NPC() = default;

		bool update() override;

		void addComponent(Component* c) override;
};

