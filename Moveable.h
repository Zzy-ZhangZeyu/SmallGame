#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "Vector2D.h"
/*! \brief Uses RK4 integration. Which can be used to simulate gravity.
I can then apply acceleration to make stuff move.*/
class Moveable
{
protected:
	Vector2D pos, vel ,acc;
	float drag, mass, elasticity, friction, density;
	float area;
public:
	Moveable();
	~Moveable();
	void intergrate(float time);//!< Intergrates using rk4
	void setAcc(Vector2D nAcc);//!< sets acceleration
	void setVel(Vector2D nVel);//!< Sets Velocity
	void setPos(Vector2D nPos);//!< sets Position
	void setCoeffient(float nDrag, float nDensity, float nElasticity, float nFriction);//!< Sets the coeffients
	Vector2D getPosition()const;//!< Returns Position
	Vector2D getVelocity()const;//!< Returns Velocity
	Vector2D getAccel()const;//!< Returns Acceleration
	Vector2D acceleration(Vector2D nPos, Vector2D nVel);//!< Calculates acceleration
	float getMass()const;//!<Calculates and Returns the Mass
	float getDrag()const;//!< Returns drag coefficent
	float getElasticity()const;//!< Returns Elasticity
	float getFriction()const;//!< Returns Friction
	float getDensity()const;//!< Returns Friction
};

#endif