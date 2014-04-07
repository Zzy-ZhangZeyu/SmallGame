/*!
@Enemy.cpp
*/

#include "Enemy.h"

Enemy::Enemy()
{
	initialised = false;
	texture = LoadTexture::getInstance();
	
}
Enemy::~Enemy(){};

void Enemy::Initialise(float height, float width, float xPos, float yPos)
{
	
	box.setSize(height,width);
	box.setCoeffient(0.f,1.0f,1.0f,0.f);
	box.setAcc(Vector2D (0,0.f));
	box.setPos(xPos,yPos);
	box.setTextureCoords(31.f*16.f,10.f*16.f);
	box.setInverseMass(1/box.getMass());
	box.setVel(Vector2D(0.f,0.f));
	animate.Initialise(Vector2D(30,10),Vector2D(31,10),200.f,&box);
}

void Enemy::Update(float time)
{
	box.Update(time);//!< INtegration
	//box.setTextureCoords(14.f*16.f,10.f*16.f);
	animate.Update(&box);//!< Animates
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(box,texture->getTexture());
}
Box * Enemy::getEnemy()
{
	return &box;
}