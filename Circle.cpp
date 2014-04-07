/*!
@Circle.cpp
*/

#include "Circle.h"

Circle::Circle()
{
}
Circle::~Circle()
{
}
Circle::Circle(float radius, unsigned int pointCount, float xPos, float yPos, float nDrag, float nDensity, float nElasticity, float nFriction)
{
	density = nDensity;
	circle.setRadius(radius);//!< sets radius
	circle.setPointCount(pointCount);//!<sets how many points it has.
	circle.setOrigin(radius,radius);//!< Seets the Origin
	pos.setXandY(xPos,yPos);//!< sets the Position
	setCoeffient(nDrag, nDensity, nElasticity, nFriction);//!< Sets all the Coeffients
	area = 3.14159265359f * (radius * radius);//!< Works out the volume using pi and radius
}

void Circle::setParams(float radius, unsigned int pointCount, float xPos, float yPos)
{
	circle.setRadius(radius);//!< sets radius
	circle.setPointCount(pointCount);//!<sets how many points it has.
	circle.setOrigin(radius,radius);//!< Seets the Origin
	pos.setXandY(xPos,yPos);//!< sets the Position
	area =  3.14159265359f * (radius * radius);
}
void Circle::Update(float time)
{
	intergrate(time);//!< Integration with RK4
	circle.setPosition(sf::Vector2f(pos.getX(),pos.getY()));//!< Updates the position
}
void Circle::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	//!< Draws the circle.
	target.draw(circle,states);
}

void Circle::setColour(sf::Color colour)
{
	circle.setFillColor(colour);//!< Change the colour of the circle.
}
float Circle::getRadius()
{
	return circle.getRadius();//!< Returns the radius.
}
