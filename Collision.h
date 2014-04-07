#ifndef COLLISION_H
#define COLLISION_H

#include "Box.h"
#include "Vector2D.h"
#include "Circle.h"
#include "Line.h"
#include "ManifoldCtoC.h"
#include "ManifoldCtoAABB.h"
#include "ManifoldAABBtoAABB.h"
/*! \brief Checks collisions*/
class Collision
{
private:
	float penetrationDepth;//!< Depth of penetration
	Vector2D normal;//!< Normal in AABB
	Vector2D normal2;//!< Normal in Circle to AABB
	float distance;//!< Penetration depth in circle to aabb
public:
	Collision();
	~Collision();
	void CircleToCircle(Circle &a, Circle &b );//!< Circle to circle detection
	bool CircleToAABB(Circle &a, Box &b, bool &hitFloor, bool &hitSide, bool &hitUnder);//!< Circle to aabb detection
	bool CircleToLine(Circle &a, Line &b);//!< Circle to line detection
	bool AABBtoAABB(Box &a, Box &b,Vector2D &Nnormal);//!<Box to Box collision detection

	void applyAABBtoAABBimpulse(Box &a, Box &b);//!< Applies Impulse AABB to AABB
	void applyCtoAABBimpulse(Circle &a, Box &b);//!< Applies Impulse Circle to AABB
};
#endif