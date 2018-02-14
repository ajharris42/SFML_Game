#pragma once

class GameEntity;

class Component
{
	public:
		Component(){}
		virtual ~Component(){}
		virtual void update(GameEntity *e) = 0;
};

