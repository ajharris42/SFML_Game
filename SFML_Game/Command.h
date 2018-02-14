#pragma once

#include "GameEntity.h"
#include "Camera.h"

/*class Command
{
	public:
		Command(){}
		virtual ~Command(){}

		virtual void execute() = 0;
};*/

class EntityCommand
{
	public:
		EntityCommand() {}
		virtual ~EntityCommand() {}

		virtual void execute(GameEntity *e) = 0;
};

class CameraCommand
{
	public:
		CameraCommand() {}
		virtual ~CameraCommand() {}

		virtual void execute(Camera *c) = 0;
};

/*class CloseWindowCommand : public Command
{
	public:
		explicit CloseWindowCommand(bool *running) { this->running = running; }
		~CloseWindowCommand(){}

		void execute() override
		{
			*running = false;
		}

	private:
		bool *running;

};*/

class MoveCommand : public EntityCommand, public CameraCommand
{
	public:
		explicit MoveCommand(GameEntity::Direction d) { this->d = d; }
		~MoveCommand(){}

		void execute(Camera *c) override
		{
			switch (d) {
			case GameEntity::UP:
				c->moveUp();
				break;
			case GameEntity::DOWN:
				c->moveDown();
				break;
			case GameEntity::LEFT:
				c->moveLeft();
				break;
			case GameEntity::RIGHT:
				c->moveRight();
				break;
			default:
				//uhhh
				break;
			}
		}

		void execute(GameEntity *e) override
		{
			switch(d){
				case GameEntity::UP:
					e->moveUp();
					break;
				case GameEntity::DOWN:
					e->moveDown();
					break;
				case GameEntity::LEFT:
					e->moveLeft();
					break;
				case GameEntity::RIGHT:
					e->moveRight();
					break;
				default:
					//uhhh
					break;
			}
		}

	private:
		GameEntity::Direction d;
};

