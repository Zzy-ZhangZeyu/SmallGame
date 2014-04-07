#ifndef TEXT_H
#define TEXT_H

#include "Font.h"
#include <SFML\Graphics.hpp>

/*! \brief Creates text that uses Mario font.*/
class Text: public sf::Drawable
{
private:
	sf::Text text;
	Font* font;//!< Will always use same font class as its a singleton. So will only load the font in once.
public:
	~Text(){};
	Text();//!<Sets size to 15 and colour to white as default.
	void setString(std::string nString);//!< Sets the string of the Text.
	void setPosition(float nX, float nY);//!< Sets the position of the Text.
	void setSize(unsigned int nSize);//!< Sets the size of the font.
	void setColour(sf::Color nColour);//!< Sets the colour of the font.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;//!< Draws 
};
#endif