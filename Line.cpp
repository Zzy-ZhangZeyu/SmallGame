/*!
@Line.cpp
*/
#include "Line.h"

Line::Line()
{
	line.resize(2);//!< Sets the size of the vertex array.
	line.setPrimitiveType(sf::Lines);//!< sets to a line
}
Line::~Line()
{
}
Line::Line(Vector2D &nStartPoint, Vector2D &nEndPoint)
{
	line.resize(2);//!< Sets the size of the vertex array.
	line.setPrimitiveType(sf::Lines);//!< sets to a line
	startP = nStartPoint;//!< start point
	endP = nEndPoint;//!< end point
	line[0].position = sf::Vector2f(startP.getX(), startP.getY());//!<Sets the start point of the line
	line[1].position = sf::Vector2f(endP.getX(), endP.getY());//!<Sets the end point of the line
}
void Line::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	//!draws the line
	target.draw(line);
}
void Line::setPoints(Vector2D nStartPoint, Vector2D nEndPoint)
{
	startP = nStartPoint;
	endP = nEndPoint;
	line[0].position = sf::Vector2f(startP.getX(), startP.getY());//!< Sets start position on the line.
	line[1].position = sf::Vector2f(endP.getX(), endP.getY());//!< Sets end position of the line.
}
Vector2D Line::getStartPosition()const
{
	return startP;
}
Vector2D Line::getEndPosition()const
{
	return endP;
}
Vector2D Line::lineNormal()
{
	return Vector2D(startP.getY()-endP.getY(), endP.getX() - startP.getX());//!< Finds the normal of the line.;
}
float Line::lineOrigin()
{
	return ((startP.getX() - endP.getX()) * startP.getY() + (endP.getY() - startP.getY()) * startP.getX());//!< Finds the origin of the line.
}