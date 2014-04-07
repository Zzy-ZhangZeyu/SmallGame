#ifndef COIN_H
#define COIN_H

#include "Animate.h"
#include "Box.h"
#include "LoadTexture.h"
/*! \brief This defines a coin that can be animated.*/
class Coin: public sf::Drawable
{
private:
	LoadTexture* texture;//!< Pointer to texture.
	Box box;//!< Creates a box object.
	Animate animate;//!< Creates an animate object.
	Vector2D startPos;//!< holds the Value of the starting Pos. Used for moving coins. Can how far Up needs to go before i delete it.
public:
	Coin();//!< Default constructor.
	~Coin(){};
	void Initialise(float height, float width, float xPos, float yPos);//!< Initialises parameters for the coin
	void Update(float time);//!< Integration Rk4 and Update animation
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;//!< Draws the coin
	Box * getCoin();//!< returns the box.
	Vector2D getStartPos()const;//!< returns the value of the starting position.
};
#endif