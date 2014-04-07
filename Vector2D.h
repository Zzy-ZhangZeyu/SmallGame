#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <SFML\Graphics.hpp>
#include <algorithm> 

/*! \brief Allows me to do calculations for the vectors. */
class Vector2D: sf::Vector2f
{
private:

public:
	Vector2D();
	~Vector2D();
	Vector2D(float nx, float ny);
	Vector2D add(Vector2D &other);//!< Adds two vectors
	Vector2D subtract(Vector2D &other);//!< Subtracts two vectors
	Vector2D scalar(float scalar);//!< Multiplys a Vector by a scalar
	Vector2D minMax(Vector2D &a, Vector2D &b);//!< Clamps the minMax values used in collision detection.
	float dotProduct(Vector2D &other);//<! Returns the dotproduct between two vectors.
	float crossProduct(Vector2D &other);//!< Returns the crossProduct between two vectors.
	float magnitude();//!< Finds the magnitude of a vector
	float getX()const;//!< Returns X value
	float getY()const;//!< Returns Y value
	void setXandY(float nx, float ny);//!< Sets X and Y value
	Vector2D getUnitVector();//!< Returns the Vector as a unit vector. Normalises.
};


#endif