#ifndef LINE_H
#define LINE_H

#include <SFML\Graphics.hpp>
#include "Vector2D.h"
/*! \brief Creates a line*/
class Line: public sf::Drawable
{
private:
	Vector2D startP, endP;//!< Start and end Point of the line
	sf::VertexArray line;//!< Defines the line
public:
	Line();//! Default Constructor
	~Line();
	Line(Vector2D &nStartPoint, Vector2D &nEndPoint);//!< Constructor sets Start and End point.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;//!< Draws the line
	void setPoints(Vector2D nStartPoint, Vector2D nEndPoint);//!< Sets the start and end points of the line
	Vector2D getStartPosition()const;//!< Returns start position
	Vector2D getEndPosition()const;//!< Returns end position
	Vector2D lineNormal();//!< Finds the normal of the line
	float lineOrigin(); //!< Finds the origin of the line
};

#endif