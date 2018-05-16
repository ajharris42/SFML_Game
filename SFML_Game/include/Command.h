#pragma once

#include "GameEntity.h"
#include "Camera.h"

class Command
{
	public:
		Command() = default;
		virtual ~Command() = default;

		virtual void execute() = 0;
};

class MoveCommand : public Command
{
	public:
		explicit MoveCommand(GameEntity::Direction d) { this->d = d; }
		~MoveCommand() = default;

		void execute() override {}
		void execute(Moveable* e) const
		{
			switch(d){
				case GameEntity::UP:
					e->MoveUp();
					break;
				case GameEntity::DOWN:
					e->MoveDown();
					break;
				case GameEntity::LEFT:
					e->MoveLeft();
					break;
				case GameEntity::RIGHT:
					e->MoveRight();
					break;
				default:
					//uhhh
					break;
			}
		}

	private:
		GameEntity::Direction d;
};

