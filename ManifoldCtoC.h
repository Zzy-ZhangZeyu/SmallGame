#ifndef MANIFOLDCTOC_H
#define MANIFOLDCTOC_H

#include "Vector2D.h"
#include "Collision.h"
#include "Circle.h"
#include <algorithm> 
/*! \brief Applies impulse and position correction of an Circle to Circle */ 

class ManifoldCtoC
{
private:
	float slop, percentCorrection;//!< Used for position correction
	float penetrationDepth;
	Vector2D normal;//!<Normal of A to B
	Vector2D contact;//!< Point of Contacts
public:
	ManifoldCtoC();//!< Default constructor
	~ManifoldCtoC();
	void Initialize(Circle &a, Circle &b, float &d);  // Precalculations for impulse solving
    void ApplyImpulse(Circle &a, Circle &b);   // Solve impulse and apply
};
#endif