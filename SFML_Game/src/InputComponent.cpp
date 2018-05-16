#include "InputComponent.h"
#include "GameEntity.h"

InputComponent::InputComponent(Input* i)
{
	this->i = i;
}

void InputComponent::update(Moveable* e) const
{
	MoveCommand* c = dynamic_cast<MoveCommand*>(i->getEntityInput());

	if (c != nullptr)
	{
		c->execute(e);

		delete c;
		c = nullptr;
	}
}

InputComponent::~InputComponent()
{

}
