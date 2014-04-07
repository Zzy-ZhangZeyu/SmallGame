/*!
@Coin.cpp
*/

#include "Coin.h"

Coin::Coin()
{
	texture = LoadTexture::getInstance();//!< Sets the texture.
	box.setSize(32,32);//!< Sets the size.
	box.setCoeffient(0.f,0.01f,0.0f,0.f);//!<sets the coeffients.
	box.setAcc(Vector2D (0,0.f));//!< sets the acc/
	box.setPos(0,0);//!< Sets pos
	box.setTextureCoords(2.f*16.f,9.f*16.f);//!< sets the texture coords
	box.setInverseMass(0);//!< Sets the inverse mass
	box.setVel(Vector2D(0.f,0.f));//!< sets the velocity
	animate.Initialise(Vector2D(29,9),Vector2D(32,9),150.f,&box);//!< Initialises the animation
}

void Coin::Initialise(float height, float width, float xPos, float yPos)
{
	startPos = Vector2D(xPos,yPos);//!< Creates a starting Position
	box.setSize(height,width);//!< SEts the size of the coin
	box.setCoeffient(0.f,0.01f,0.0f,0.f);//!< sets the coeffients
	box.setAcc(Vector2D (0,0.f));//!< Sets the acceleration
	box.setPos(xPos,yPos);//!< sets the Position
	box.setTextureCoords(2.f*16.f,9.f*16.f);//!< Sets the texture coordinates.
	box.setInverseMass(0);//!< Sets the inverse mass
	box.setVel(Vector2D(0.f,0.f));//!< SEts the velocity
	animate.Initialise(Vector2D(29,9),Vector2D(32,9),150.f,&box);//!< Initialises the animation

}
void Coin::Update(float time)
{
	box.Update(time);//!< INtegration
	animate.Update(&box);//!< Animates the coin
}
void Coin::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(box,texture->getTexture());//!< Draws the box pointing to the texture.
}
Box * Coin::getCoin()
{
	return &box;//!< Returns a pointer to the box.
}
Vector2D Coin::getStartPos()const
{
	return startPos;//!< returns the start Position.
}

