#include "RenderComponent.h"

#include "GameEntity.h"

RenderComponent::RenderComponent()
{
	g = Graphics::getInstance();
}

void RenderComponent::update(GameEntity *e)
{
	g->draw(e->getTextureBounds(), e->getRenderStates());
}


RenderComponent::~RenderComponent()
{

}
