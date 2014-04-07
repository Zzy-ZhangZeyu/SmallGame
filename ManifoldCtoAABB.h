#ifndef MANIFOLDCTOAABB_H
#define MANIFOLDCTOAABB_H

#include "Vector2D.h"
#include "Collision.h"
#include "Circle.h"
#include "Box.h"
#include <algorithm> 
#define REFRESH_RATE 0.00833f
/*! \brief Applies impulse and position correction of an Circle to Box */ 
class ManifoldCtoAABB
{
private:
	float slop, percentCorrection;//!< Used for position correction
	float penetrationDepth;//!< Depth of penetration
	Vector2D normal;//!<Normal of A to B
	Vector2D contact;//!< Point of Contacts
public:
	ManifoldCtoAABB();//!< Default constructor
	~ManifoldCtoAABB();
	void Initialize(Circle &a, Box &b, float &d, Vector2D &nNormal);  //!< Precalculations for impulse solving
    void ApplyImpulse(Circle &a, Box &b);   //!< Solve impulse and apply
};


#endif