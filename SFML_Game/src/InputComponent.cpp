#include "InputComponent.h"

#include "GameEntity.h"

InputComponent::InputComponent(Input* i)
{
	this->i = i;
}

void InputComponent::update(GameEntity* e)
{
	EntityCommand* c = i->getEntityInput();

	if (c != nullptr)
	{
		c->execute(e);

		delete c;
		c = nullptr;
	}
}

void InputComponent::update(Camera* c) const
{
	CameraCommand* command = i->getCameraInput();

	if (command != nullptr)
	{
		command->execute(c);

		delete command;
		command = nullptr;
	}
}

InputComponent::~InputComponent()
{

}
