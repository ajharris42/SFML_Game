#include "AIInputComponent.h"

#include "GameEntity.h"

AIInputComponent::AIInputComponent()
{
}


void AIInputComponent::update(GameEntity *e)
{
	//Temporary test code
	if(e->getX() >= 0 && e->getX() <= 640 && e->getDirection() == e->LEFT)
	{
		e->moveLeft();
	}
	else if(e->getX() >= 0 && e->getX() <= 640 && e->getDirection() == e->RIGHT)
	{
		e->moveRight();
	}
	else if(e->getX() <= 0)
	{
		e->moveRight();
	}
	else if(e->getX() >= 640)
	{
		e->moveLeft();
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
