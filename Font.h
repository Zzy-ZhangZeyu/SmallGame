#ifndef FONT_H
#define FONT_H

#include <SFML\Graphics.hpp>
/*! \brief Loads in the NES font*/
class Font
{
private:
	sf::Font font;//!< Loads in a font.
	static bool instanceFlag;//!< Creates a bool. Thats allows me to check if a new font has been made.
	static Font *myFont;//!< Creates a pointer of font.
	Font();
public:
	~Font()//!< Desconstructor.
	{
		instanceFlag = false;
	}
	static Font* getInstance();//!< Returns the font class. Creates a new font if. There isn't one.
	sf::Font const* getFont()const;//!< returns a constant pointer of font.
	
};
#endif