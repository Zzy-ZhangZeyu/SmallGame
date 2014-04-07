#include "Manifold.h"

Manifold::Manifold()
{

}
void Manifold::Initialize(Circle &a, Circle &b, float &d)
{
	

	normal = a.getPosition().subtract(b.getPosition()).getUnitVector();//!< Normal between the two circles.
	float sumOfRadii = a.getRadius() + b.getRadius();//!< gets the sum of the radii
	penetrationDepth = sumOfRadii - d ;//!<  works out the depth of penetration
	contact = normal.scalar(a.getRadius()).add(a.getPosition()); //!< Calculates the position of contact
	
}
void Manifold::ApplyImpulse(Circle &a, Circle &b)
{
	//c= max(pd-slop,0)/(1/massA+1/massB) *p *n
	percentCorrection = 0.95f;
	slop = 0.04f;
	Vector2D c = normal.scalar(std::max(penetrationDepth - slop, 0.f) * percentCorrection);//!<  Works out the position correction
	a.setPos(a.getPosition().add(c));//!< sets circle A to new position
	b.setPos(b.getPosition().subtract(c));//!< sets circle B to new position
	//! Circle to Circle
	float dotProduct;
	//!SV = -2 * n * n.v
	dotProduct = normal.dotProduct(a.getVelocity().subtract(b.getVelocity()));//!< dotproduct of (va-vb).n
	
	//!Momentum = mass * velocity so ma * va + mb * vb = ma * va' + mb * vb'
	float e = std::min(a.getElasticity(), b.getElasticity());//!< Calculates Restitution

	//! Calculate the impulse scalar
	float j = -(1+ e) * dotProduct;
	float inverseMass = 1/ a.getMass() + 1/b.getMass();
	j /= inverseMass;


	//!Friction Impulse Scalar
	//t = (va - vb) - ((va-vb).n)*n
	//p = -(va-vb).t / 1/ma + 1/mb
	//! Tangential line to the collision normal
	Vector2D avgV = a.getVelocity().subtract(b.getVelocity());
	Vector2D t = normal.scalar(dotProduct);
	t = avgV.subtract(t);
	t = t.getUnitVector();
	//!Impulse scalar p
	float p = -avgV.dotProduct(t);
	p /= inverseMass;
	
	//! Coefficent of friction
	float friction = std::sqrt(a.getFriction() * a.getFriction() + b.getFriction() * b.getFriction());

	Vector2D impulse = normal.scalar(j);
	
	
	//! Apply the impulse
	a.setVel(a.getVelocity().add(impulse.scalar(1/a.getMass())));//!< New Velocity of A
	b.setVel(b.getVelocity().subtract(impulse.scalar(1/b.getMass())));//!< New velocity of B

	if ( p <= j * friction)
	{
		impulse = Vector2D(p * REFRESH_RATE,p * REFRESH_RATE) ;
	}
	else 
	{
		impulse = Vector2D(-j * friction * REFRESH_RATE,-j * friction * REFRESH_RATE);
	}

	a.setVel(a.getVelocity().add(impulse.scalar(1/a.getMass())));//!< New Velocity of A
	b.setVel(b.getVelocity().subtract(impulse.scalar(1/b.getMass())));//!< New velocity of B
}