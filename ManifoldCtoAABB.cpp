/*!
@ManifoldCtoAABB.cpp
*/
#include "ManifoldCtoAABB.h"

ManifoldCtoAABB::ManifoldCtoAABB()
{
}
ManifoldCtoAABB::~ManifoldCtoAABB()
{

}
void ManifoldCtoAABB::Initialize(Circle &a, Box &b, float &d, Vector2D &nNormal)  // Precalculations for impulse solving
{

	normal = nNormal;//.getUnitVector();//!< Normal between the two circles.
	penetrationDepth =  -d ;//!<  works out the depth of penetration
	contact = normal.scalar(a.getRadius()).add(a.getPosition()); //!< Calculates the position of contact
}
void ManifoldCtoAABB::ApplyImpulse(Circle &a, Box &b)   // Solve impulse and apply
{
	float inverseMass = 1/ a.getMass() + 1/b.getMass();
	float inverseMassA = 1/a.getMass();
	//c= max(pd-slop,0)/(1/massA+1/massB) *p *n
	percentCorrection = 1.55f;
	slop = 0.0001f;
	Vector2D c = normal.scalar((std::max(penetrationDepth - slop, 0.f)/inverseMass) * percentCorrection);//!<  Works out the position correction
	a.setPos(a.getPosition().subtract(c.scalar(1/a.getMass())));//!< sets circle A to new position
	//b.setPos(b.getPosition().add(c.scalar(1/b.getMass())));//!< sets Box B to new position
	//! Circle to Circle
	float dotProduct;
	//!SV = -(1+e) * n * n.v
	dotProduct = normal.dotProduct(a.getVelocity().subtract(b.getVelocity()));//!< dotproduct of (va-vb).n

	float e = std::min(a.getElasticity(), b.getElasticity());//!< Calculates Restitution

	//! Calculate the impulse scalar
	float j = -(1+ e) * dotProduct;
	//float inverseMass = 1/ a.getMass() + 1/b.getMass();
	j /= inverseMass;


	//!Friction Impulse Scalar
	//t = (va - vb) - ((va-vb).n)*n
	//p = -(va-vb).t / 1/ma + 1/mb
	//! Tangential line to the collision normal
	/*Vector2D avgVel = a.getVelocity().subtract(b.getVelocity());
	Vector2D t = avgVel.subtract( normal.scalar(dotProduct));

	//t = t.getUnitVector();

	//!Impulse scalar p
	float p = -avgVel.dotProduct(t);
	p /= inverseMass;

	//! Coefficent of friction
	float friction = std::sqrt(powf(a.getFriction() ,2.f) + powf(b.getFriction(),2.f));*/

	Vector2D impulse = normal.scalar(j);
	//! Apply the impulse
	a.setVel(a.getVelocity().add(impulse.scalar(inverseMassA)));//!< New Velocity of A
	b.setVel(b.getVelocity().subtract(impulse.scalar(b.getInverseMass())));//!< New velocity of B

	/*if ( p <= j * friction)
	{
	impulse = Vector2D(0, p * REFRESH_RATE);
	}
	else 
	{
	impulse = Vector2D(0,-j * friction * REFRESH_RATE);
	}

	a.setVel(a.getVelocity().add(impulse.scalar(inverseMassA)));//!< New Velocity of A
	b.setVel(b.getVelocity().subtract(impulse.scalar(inverseMassB)));//!< New velocity of B*/

}