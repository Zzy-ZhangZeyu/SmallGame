#ifndef MANIFOLDAABBTOAABB_H
#define MANIFOLDAABBTOAABB_H

#include "Collision.h"
/*! \brief Applies impulse and position correction of an Box to Box */ 
class ManifoldAABBtoAABB
{
private:
	float slop, percentCorrection;//!< Used for position correction
	float penetrationDepth;//!< Depth of penetration
	Vector2D normal;//!<Normal of A to B
	
public:
	ManifoldAABBtoAABB();//!< Default constructor
	~ManifoldAABBtoAABB();
	void Initialize(Box &a, Box &b, float &d, Vector2D &nNormal); //!< Precalculations for impulse solving
	void ManifoldAABBtoAABB::ApplyImpulse(Box &a, Box &b); //!< Solve impulse and apply
};
#endif