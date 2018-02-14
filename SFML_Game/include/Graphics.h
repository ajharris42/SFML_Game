#pragma once

#include "SFML/Graphics.hpp"

/*
	This is a singleton class.  This is the best way currently to manage rendering.
	Leave it as a singleton, unless you have a really good reason to change it.
*/

class Graphics 
{
	public:
		static Graphics *getInstance();

		void clearWindow();
		void updateWindow();
		void updateView() const;

		sf::RenderWindow *getWindow(){return &window;}

		void draw(const sf::Drawable &d);
		void draw(const sf::VertexArray &va, const sf::RenderStates &renderStates);

		void setView(sf::View view);

		sf::Texture getTexture(const char *key);

		float viewW;
		float viewH;

		sf::View view;

		sf::FloatRect viewRegion;
	private:
		Graphics();
		Graphics(const Graphics&) = delete;
		Graphics &operator=(const Graphics&) = delete;

		~Graphics();

		static Graphics *pInstance;

		sf::RenderWindow window;

		std::map<const char *, sf::Texture> textures;
		std::map<const char *, sf::Texture>::iterator itr;
};