/*!
@Font.cpp
*/

#include "Font.h"

bool Font::instanceFlag = false;
Font * Font::myFont = NULL;
Font::Font()
{
	if (!font.loadFromFile("./Fonts/NES.ttf"))//!< Font only gets loaded once.
	{
		//!<error
	}
}
Font* Font::getInstance()
{
	//!Creates a new player then returns player.
	if(!instanceFlag)
	{
		myFont = new Font();
		instanceFlag = true;
		return myFont;
	}
	//! Returns the player if there is already a player.
	else return myFont;
}
sf::Font const* Font::getFont()const
{
	return &font;//!< Returns the loaded font.
}
