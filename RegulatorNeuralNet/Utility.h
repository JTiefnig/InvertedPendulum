#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"


// for later use
class Utility
{
public:
	Utility();
	~Utility();
};




// Slingleton so that font is just loaded once
//
//
class CustomFont
{
	sf::Font font;


	CustomFont() 
	{
		if (!font.loadFromFile("arial.ttf"))
		{
			std::cout << "font not found" << std::endl;
		}
	}

public:

	static CustomFont&  getInstance()
	{
		static CustomFont instance;

		return instance;
	}


	static sf::Font& Font()
	{
		return getInstance().font;
	}

	

	CustomFont(CustomFont const&) = delete;
	void operator=(CustomFont const&) = delete;

};