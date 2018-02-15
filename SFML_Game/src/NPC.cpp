#include "NPC.h"

#include "InputComponent.h"
#include "RenderComponent.h"

NPC::NPC(InputComponent *i, RenderComponent *g)
{
	texture.loadFromFile("gfx/player.png");

	inputComponent = i;
	renderComponent = g;

	renderStates.texture = &texture;
}

bool NPC::update()
{
	if (inputComponent != nullptr)
	{
		inputComponent->update(this);

		//Update where the texture should be applied
		textureBounds[0].position = sf::Vector2f(position.x, position.y);
		textureBounds[1].position = sf::Vector2f((position.x + width), position.y);
		textureBounds[2].position = sf::Vector2f((position.x + width), (position.y + height));
		textureBounds[3].position = sf::Vector2f(position.x, (position.y + height));

		return true;
	}

	return false;
}

void NPC::render()
{
	if (renderComponent != nullptr)
		renderComponent->update(this);
}

void NPC::addComponent(Component* c)
{

}

NPC::~NPC()
{

}
