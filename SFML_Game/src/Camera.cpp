#include "Camera.h"
#include "Command.h"
#include "InputComponent.h"

Camera::Camera(InputComponent* i)
{
	inputComponent = i;

	g = Graphics::getInstance();

	screenX = &g->viewW;
	screenY = &g->viewH;

	g->setView(initializeView());

	position = sf::Vector2f(0.0f, 0.0f);

	bounds.left = position.x;
	bounds.top = position.y;
	bounds.width = *screenX;
	bounds.height = *screenY;
}

void Camera::MoveUp()
{
	position.y -= 10;
}

void Camera::MoveDown()
{
	position.y += 10;
}

void Camera::MoveLeft()
{
	position.x -= 10;
}

void Camera::MoveRight()
{
	position.x += 10;
}

bool Camera::update() 
{
	/*if (i->keyPressed("W"))
		position.y -= 10;    //There should probably be a deltaT in there somewhere
	if (i->keyPressed("S"))
		position.y += 10;
	if (i->keyPressed("A"))
		position.x -= 10;
	if (i->keyPressed("D"))
		position.x += 10;*/

	if(inputComponent != nullptr)
	{
		inputComponent->update(this);
	}
	else
	{
		return false;
	}

	bounds.left = position.x;
	bounds.top = position.y;
	bounds.width = *screenX;
	bounds.height = *screenY;

	mainView.reset(sf::FloatRect(bounds.left, bounds.top, bounds.width, bounds.height));
	g->setView(mainView);

	return true;
}

sf::View Camera::initializeView() 
{
	mainView.reset(sf::FloatRect(0, 0, *screenX, *screenY));
	mainView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	return mainView;
}

Camera::~Camera() 
{

}
