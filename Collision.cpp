/*!
@Collision.cpp
*/

#include "Collision.h"


Collision::Collision(){}

Collision::~Collision(){}

void Collision::CircleToCircle(Circle &a, Circle &b)
{
	ManifoldCtoC m;
	Vector2D diff = a.getPosition().subtract(b.getPosition());//!< Origin of position subtracting origin of other position; 
	float dist = diff.magnitude();//!< Gets the length between the two origins.
	float sumOfRadii = a.getRadius() + b.getRadius();//!< Sum of the radii

	if (dist > sumOfRadii)//!< Exits early if no collision detection.
	{
		return;
	}
	//!send circles and the calculated distance to the manifold.
	m.Initialize(a,b, dist);//!< Initializes the manifold.
	m.ApplyImpulse(a,b);
}
bool Collision::CircleToAABB(Circle &a, Box &b, bool &hitFloor,bool &hitSide, bool &hitUnder)
{
	
	Vector2D extents(b.getWidth()/2,b.getHeight()/2);//!< puts the extents of the box into a vector2d.
	Vector2D disti = b.getPosition().subtract(a.getPosition());//!< Finds the distance between the two origins.
	Vector2D clamp = clamp.minMax(disti,extents);//!<Clamp closet point?
	disti = disti.subtract(clamp);//!< Calculates the distance from the box. In the X and Y.
	distance = disti.magnitude() - a.getRadius();//!< Gets the length between the two objects. 
	if(distance > 0)
	{
		return false; //!<Exits if the distance is greater than 0
	}
	//return true;
	normal2 = disti.getUnitVector();//!< Calculates the normal
	//!Used to find out if ive hit top side or under
	if(normal2.getY() > 0.2f)
	{ 
		hitFloor = true;
	}
	else hitFloor = false;
	if(normal2.getY() < -0.5f)
	{ 
		hitUnder = true;
	}
	if(normal2.getX() == -1.f || normal2.getX() == 1.f )
	{ 
		hitSide = true;
	}

	return true;
}

bool Collision::CircleToLine(Circle &a, Line &b)
{
	Vector2D normal = b.lineNormal();//!< Gets the normal of the line and sets to a new Vector2D
	float mag = normal.magnitude();//!< Finds the magnitude of the normal.
	float c = b.lineOrigin();//!< Find the origin value of the line.
	c /= mag;//!< Normalises the origin value.
	Vector2D normal2 = normal.getUnitVector();//!< normalises the normal.
	float distance = (a.getPosition().dotProduct(normal2) + (c));//!< Finds the distance away from the point.  distance = p.n + 
	return (distance >= 0 - a.getRadius()); //!< If the distance is 0 or less than 0. Return true.
}
bool Collision::AABBtoAABB(Box &a, Box &b, Vector2D &Nnormal)
{
	ManifoldAABBtoAABB m;
	//!Min and max collision. Checks if the two boxes have collided.
	Vector2D centreDist = b.getPosition().subtract(a.getPosition());
	//! Overlapping in X.
	float xLap =a.getWidth()/2 + b.getWidth()/2 - std::abs(centreDist.getX());
	float yLap = a.getHeight()/2 + b.getHeight()/2 - std::abs(centreDist.getY());
	//! Overlapping in Y.
	if(xLap > 0)
	{

		if (yLap > 0)
		{
			if (xLap > yLap)
			{

				if(centreDist.getY() < 0)
				{
					normal.setXandY(0,-1);//!< Collides Top of A with bottom of B
				}
				else
				{
					normal.setXandY(0,1);//!< Collides Bottom of box A with top of box B

				}
				penetrationDepth = yLap;//!< Sets the penetration depth according to the collision
			}
			else
			{
				//point normal towards b as n is from A to B on y axis
				if(centreDist.getX() < 0)
				{
					normal.setXandY(1,0);//!< Collides Left of box A with Right of Box B
				}
				else
				{
					normal.setXandY(-1,0);//!< Collides Right of box A with Left of Box B
				}
				penetrationDepth = xLap;//!< Sets the penetration depth
			}
		}
		else{ return false;}
	}
	else{ return false;}
	
	Nnormal = normal;//!< return the normal. To use for enemies.
	return true;

}

void Collision::applyAABBtoAABBimpulse(Box &a, Box &b)
{
	ManifoldAABBtoAABB m;
	m.Initialize(a,b,penetrationDepth,normal);
	m.ApplyImpulse(a,b);
}
void Collision::applyCtoAABBimpulse(Circle &a, Box &b)
{
	ManifoldCtoAABB m;
	m.Initialize(a,b, distance, normal2);
	m.ApplyImpulse(a,b);
}