#pragma once

#include "stdafx.h"
#include "Command.h"

class Input 
{
	public:
		//Do not make explicit
		Input(sf::RenderWindow *window);
		~Input();
		static bool closeWindow();
		static void pollEvents();

		EntityCommand *getEntityInput();
		CameraCommand *getCameraInput();
	private:
		//@TODO:Being static is causing problems
		static sf::RenderWindow *window;

		static bool close;
};