/*!
@Box.cpp
*/

#include "Box.h"

Box::Box()
{
	destroyable =false;//!< Default
	questionMark = false;//!< Default
}

Box::~Box(){}

void Box::setParams(Vector2D pos, Vector2D TexCoord, Vector2D size)
{
	setCoeffient(0.05f,6.f,1.0f,0.0f);//!< Sets the coEfficent of the box. Drag, density, elasticity.
	setSize(size.getY(),size.getX());//!< Sets the size of the box.
	setTextureCoords(TexCoord.getX(),TexCoord.getY());//!< Places the texture coordinates.
	setPos(pos.getX(),pos.getY());//!< Sets the Pos of the box.
	setInverseMass(0);//!< Sets the inverseMass to 0 as default.
}

Box::Box(float &nheight, float &nWidth)
{
	//! SEts the height width and area of the box.
	height = nheight;
	width = nWidth;
	area = height * width;
	destroyable =false;
}
void Box::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	//!draw the rectangle
	target.draw(rect,states);
}
void Box::setSize(float nheight, float nWidth)
{
	//!< Sets the size of the box.
	height = nheight;
	width = nWidth;
	area = height * width;
	
}
void Box::setPos(float nxPos, float nyPos)
{
	//!Sets the Position using floats.
	pos.setXandY(nxPos, nyPos);
	rect.resize(5);
	rect.setPrimitiveType(sf::Quads);
	//!Top left point
	rect[0].position = sf::Vector2f(pos.getX() - width /2 , pos.getY() -  height/2);
	//!Bottom Left
	rect[1].position = sf::Vector2f(pos.getX()  - width /2, pos.getY() + height /2);
	//!Bottom Right
	rect[2].position = sf::Vector2f(pos.getX()  + width /2, pos.getY() + height /2);
	//!Top Right
	rect[3].position = sf::Vector2f(pos.getX()  + width /2, pos.getY() - height /2);
}
void Box::setPos(Vector2D nPos)
{
	//!Sets the Position using Vector2D.
	pos.setXandY(nPos.getX(), nPos.getY());
	rect.resize(5);
	rect.setPrimitiveType(sf::Quads);
	//!Top left point
	rect[0].position = sf::Vector2f(pos.getX() - width /2 , pos.getY() -  height/2);
	//!Bottom Left
	rect[1].position = sf::Vector2f(pos.getX()  - width /2, pos.getY() + height /2);
	//!Bottom Right
	rect[2].position = sf::Vector2f(pos.getX()  + width /2, pos.getY() + height /2);
	//!Top Right
	rect[3].position = sf::Vector2f(pos.getX()  + width /2, pos.getY() - height /2);
}
void Box::Update(float time)
{
	//!Updates the Position and integrates.
	intergrate(time);//!< RK4 integration
	//!Top left point
	rect[0].position = sf::Vector2f(pos.getX() - width /2 ,pos.getY()-  height/2);
	//!Bottom Left
	rect[1].position = sf::Vector2f(pos.getX() - width /2, pos.getY() + height /2);
	//!Bottom Right
	rect[2].position = sf::Vector2f(pos.getX() + width /2, pos.getY() + height /2);
	//!Top Right
	rect[3].position = sf::Vector2f(pos.getX() + width /2, pos.getY() - height /2);
	rect[4].position =  sf::Vector2f(pos.getX() - width /2 , pos.getY() -  height/2);
}
void Box::setInverseMass(float nInverseMass)
{
	inverseMass = nInverseMass;//!< Sets the inverseMass
}
float Box::getInverseMass()const
{
	return inverseMass;//!< Returns value of inverseMass
}
Vector2D Box::getPosition()const
{
	return pos;//!< returns the Position
}

float Box::getHeight()const
{
	return height;
}
float Box::getWidth()const
{
	return width;
}
void Box::setTextureCoords(float nx, float ny)
{
	//Sets the texture coordinates to 16x16. 
	rect[0].texCoords = sf::Vector2f(nx, ny);
	rect[1].texCoords = sf::Vector2f(nx , ny+16);
	rect[2].texCoords = sf::Vector2f(nx+16, ny+16);
	rect[3].texCoords = sf::Vector2f(nx+16, ny);
}
void Box::setTextureCoords(float nx, float ny, float nwidth, float nheight)
{
	//Sets the texture coordinates to 16x16. 
	rect[0].texCoords = sf::Vector2f(nx, ny);
	rect[1].texCoords = sf::Vector2f(nx , ny+nheight);
	rect[2].texCoords = sf::Vector2f(nx+nwidth, ny+nheight);
	rect[3].texCoords = sf::Vector2f(nx+nwidth, ny);
}
void Box::setDestroyable(bool b)
{
	destroyable = b;
}
bool Box::getDestroyable()const
{
	return destroyable;
}
void Box::setQuestionBlock(bool b)
{
	questionMark = b;
}
bool Box::getQuestionBlock()const
{
	return questionMark;
}