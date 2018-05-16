#include "AIInputComponent.h"

#include "GameEntity.h"

AIInputComponent::AIInputComponent()
{
}


void AIInputComponent::update(GameEntity* e)
{
	const sf::Vector2f pos = e->getPosition();

	//Temporary test code
	if(pos.x >= 0 && pos.x <= 640 && e->getDirection() == e->LEFT)
	{
		e->MoveLeft();
	}
	else if(pos.x >= 0 && pos.x <= 640 && e->getDirection() == e->RIGHT)
	{
		e->MoveRight();
	}
	else if(pos.x <= 0)
	{
		e->MoveRight();
	}
	else if(pos.x >= 640)
	{
		e->MoveLeft();
	}

	/*if(e->getX() >= 640)
	{
		e->moveLeft();
	}
	else if(e->getX() <= 0)
	{
		e->moveRight();
	}*/
}


AIInputComponent::~AIInputComponent()
{

}
