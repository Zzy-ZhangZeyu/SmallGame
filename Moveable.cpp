/*!
@Moveable.cpp
*/
#include "Moveable.h"

Moveable::Moveable()
{

}
Moveable::~Moveable()
{

}
void Moveable::intergrate(float time)
{

	float h = time;//Timestep
	Vector2D p1,p2,p3,p4;//!<Positions
	Vector2D v1,v2,v3,v4;//!<Velocities
	Vector2D a1,a2,a3,a4;//!< Accelerations
	Vector2D newPos, newVel;//!Empty vector of newPos and newVel
	p1 = pos;//!< First point of curve
	v1 = vel;//!< First point of curve
	a1 = acceleration(p1,v1);//!< Calls Acceleration function
	p2 = p1.add(v1.scalar(h / 2.f));//!< Second point of curve
	v2 = v1.add(a1.scalar(h/2.f));//!< Second point of curve
	a2 = acceleration(p2,v2);//!<Updates Acceleration
	p3 = p1.add(v2.scalar(h / 2.f));//!< Third point of curve
	v3 = v1.add(a2.scalar(h / 2.f));//!< Third point of curve
	a3 = acceleration(p3,v3);//!<Updates Acceleration
	p4 = p1.add(v3.scalar(h));//!< Fourth point of curve
	v4 = v1.add(a3.scalar(h));//!< Fourth point of curve
	a4 = acceleration(p4,v4);//!<Updates Acceleration
	newPos = pos.add((v1.add(v2.scalar(2)).add(v3.scalar(2)).add(v4)).scalar(h));//!<Calculates new Position
	newVel = vel.add((a1.add(a2.scalar(2)).add(a3.scalar(2)).add(a4)).scalar(h));//!<Calculates new Velocity
	pos = newPos;//!<Applys the new pos.
	vel = newVel;//!<Applys the new Vel.

}
void Moveable::setAcc(Vector2D nAcc)
{
	acc = nAcc;
}
void Moveable::setVel(Vector2D nVel)
{
	vel = nVel;
}
void Moveable::setPos(Vector2D nPos)
{
	pos = nPos;
}
void Moveable::setCoeffient(float nDrag, float nDensity, float nElasticity, float nFriction)
{
	drag = nDrag;
	elasticity = nElasticity;
	density = nDensity;
	friction = nFriction;
	mass = nDensity * area;
}

Vector2D Moveable::getPosition()const
{
	return pos;
}
Vector2D Moveable::getVelocity()const
{
	return vel;
}
Vector2D Moveable::getAccel()const
{
	return acc;
}
Vector2D Moveable::acceleration(Vector2D nPos, Vector2D nVel)
{
	return Vector2D(acc.getX(), acc.getY() - drag * vel.getY());
}
float Moveable::getMass()const
{
	return mass;
}
float Moveable::getElasticity()const
{
	return elasticity;
}
float Moveable::getDrag()const
{
	return drag;
}
float Moveable::getFriction()const
{
	return friction;
}
float Moveable::getDensity()const
{
	return density;
}