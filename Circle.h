#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML\Graphics.hpp>
#include "Vector2D.h"
#include "Box.h"
#include "Moveable.h"

/*! \brief Creates a circle. This is used for mario.*/
class Circle: public sf::Drawable, public Moveable
{
private:
	sf::CircleShape circle;//!< Creates a circle
public:
	Circle();//!< Default Constructor
	~Circle();
	Circle(float radius, unsigned int pointCount, float xPos, float yPos, float nDrag, float nDensity, float nElasticity, float nFriction);//!< Constructor that can set parameters of the circle.
	void setParams(float radius, unsigned int pointCount, float xPos, float yPos);//!< sets Parameters of the circle.
	void Update(float time);//!< Updates the position vis integration.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;//!< Draws the circle
	void setColour(sf::Color colour);//!< Sets the colour
	float getRadius();//!< Returns the radius of the circle.
};


#endif