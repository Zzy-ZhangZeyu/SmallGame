/*!
@Text.cpp
*/
#include "Text.h"

Text::Text()
{
	font = Font::getInstance();//!< Gets the pointer to font.
	text.setFont(*font->getFont());//!< Whenever an object of Text is created. It will point to the correct font instead of loading a new one.
	text.setColor(sf::Color::White);//!< Sets a default colour to white.
	text.setCharacterSize(15);//!< Default size of 15.
}
void Text::setPosition(float nX, float nY)
{
	text.setPosition(nX,nY);//!< Sets the position of the fonts.
}
void Text::setString(std::string nString)
{
	text.setString(nString);//!< Sets the string of writing.
}
void Text::setSize(unsigned int nSize)
{
	text.setCharacterSize(nSize);//!< Sets the size of the fonts.
}
void Text::setColour(sf::Color nColour)
{
	text.setColor(nColour);//!< SEts the colour of the font.
}
void Text::draw(sf::RenderTarget &target, sf::RenderStates states)const//!< Draws the circle
{
	target.draw(text,states);//!< Draw the font.
} 