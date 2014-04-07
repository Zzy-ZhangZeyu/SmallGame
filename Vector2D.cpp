/*!
@UI.cpp
*/
#include "Vector2D.h"


Vector2D::Vector2D()
{
	x = 0.f;
	y = 0.f;
}
Vector2D::~Vector2D()
{
}
Vector2D::Vector2D(float nx, float ny)
{
	x = nx;
	y = ny;
}
Vector2D Vector2D::add(Vector2D &other)
{
	return Vector2D(x + other.x, y + other.y);
}
Vector2D Vector2D::subtract(Vector2D &other)
{
	return Vector2D(x - other.x, y - other.y);
}
Vector2D Vector2D::scalar(float scalar)
{
	return Vector2D(x*scalar,y*scalar);
}
Vector2D Vector2D::minMax(Vector2D &a, Vector2D &b)
{
	float rX = 0.f;
	float rY = 0.f;

	if(a.getX() >= 0)
	{
		rX = std::min(a.getX(), b.getX());
	}
	else if(a.getX() < 0)
	{
		rX = std::max(a.getX(), -b.getX());
	}
	if(a.getY() >= 0)
	{
		rY = std::min(a.getY(), b.getY());
	}
	else if(a.getY() < 0)
	{
		rY = std::max(a.getY(), -b.getY());
	}
	return Vector2D(rX,rY);
}
float Vector2D::dotProduct(Vector2D &other)
{
	return x * other.x + y * other.y;
}
float Vector2D::crossProduct(Vector2D &other)
{
	return x*other.y - y*other.x;
}
float Vector2D::magnitude()
{
	return sqrtf(powf(x,2.f)+powf(y,2.f));
}
float Vector2D::getX()const
{
	return x;
}
float Vector2D::getY()const
{
	return y;
}
Vector2D Vector2D::getUnitVector()
{
	float mag = magnitude();
	return Vector2D (x/mag, y/mag);
}
void Vector2D::setXandY(float nx, float ny)
{
	x = nx;
	y = ny;
}
