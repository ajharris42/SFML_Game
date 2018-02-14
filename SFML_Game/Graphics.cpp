#include "Graphics.h"

Graphics *Graphics::pInstance = nullptr;


Graphics *Graphics::getInstance()
{
	if(pInstance == nullptr)
	{
		pInstance = new Graphics();
	}

	return pInstance;
}

Graphics::Graphics()
{
	viewW = 640; viewH = 480;

	window.create(sf::VideoMode(viewW, viewH), "Civ");

	window.clear(sf::Color::White);

	//window.setFramerateLimit(60);

	//textures["Sky"].loadFromFile("gfx/sky.png");

}

void Graphics::clearWindow()
{
	window.clear(sf::Color::Black);
}

sf::Texture Graphics::getTexture(const char *key)
{
	itr = textures.find(key);

	if(itr != textures.end())
		return itr->second;
		
	return itr->second;
}

void Graphics::draw(const sf::Drawable &d)
{
	window.draw(d);
}

void Graphics::draw(const sf::VertexArray &va, const sf::RenderStates &renderStates)
{
	window.draw(va, renderStates);
}

void Graphics::setView(sf::View view) 
{
	this->view = view;

	window.setView(view);
}

void Graphics::updateWindow()
{
	window.display();
}

void Graphics::updateView() const
{

}

Graphics::~Graphics()
{
	window.close();
}