#ifndef MANIFOLD_H
#define MANIFOLD_H

#include "Vector2D.h"
#include "Collision.h"
#include "Circle.h"
#include <algorithm> 

#define REFRESH_RATE 0.005f

class Manifold
{
private:
	float slop, percentCorrection;//!< Used for position correction
	float penetrationDepth;//!< Depth of penetration
	Vector2D normal;//!<Normal of A to B
	Vector2D contact;//!< Point of Contacts
public:
	Manifold();//!< Default constructor
	void Initialize(Circle &a, Circle &b, float &d);  // Precalculations for impulse solving
    void ApplyImpulse(Circle &a, Circle &b);   // Solve impulse and apply
};
#endif