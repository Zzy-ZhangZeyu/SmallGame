#ifndef LOADTEXTURE_H
#define LOADTEXTURE_H

#include <SFML\Graphics.hpp>
#include <string>
/*! \brief Can create anywhere and will only load the texture first time.
Then just return the pointer of texture to use this.*/
class LoadTexture
{
private:
	sf::Texture texture;//!< sfml Texture
	static bool instanceFlag;//!< Creates a bool. Thats allows me to check if a new Loadtexture has been made.
	static LoadTexture *myTexture;//!< Creates a pointer of Loadtexture.
	LoadTexture();
public:
	~LoadTexture();
	static LoadTexture* getInstance();//!< Returns the Loadtexture class. Creates a new Loadtexture if. There isn't one.
	sf::Texture const* getTexture()const;//!< returns a pointer to teh texture.
};
#endif