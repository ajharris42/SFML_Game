#include "NPC.h"

#include "InputComponent.h"
#include "RenderComponent.h"

NPC::NPC(const sf::Vector2f &position, InputComponent* i) : GameEntity(position)
{
	texture.loadFromFile("gfx/player.png");

	inputComponent = i;

	renderStates.texture = &texture;
}

bool NPC::update()
{
	if (inputComponent != nullptr)
	{
		inputComponent->update(this);

		const sf::Vector2f pos = getPosition();

		//Update where the texture should be applied
		textureBounds[0].position = sf::Vector2f(pos.x, pos.y);
		textureBounds[1].position = sf::Vector2f((pos.x + width), pos.y);
		textureBounds[2].position = sf::Vector2f((pos.x + width), (pos.y + height));
		textureBounds[3].position = sf::Vector2f(pos.x, (pos.y + height));

		return true;
	}

	return false;
}

void NPC::addComponent(Component* c)
{

}
