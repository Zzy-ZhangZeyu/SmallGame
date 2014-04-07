/*!
@Player.cpp
*/
#include "Player.h"

bool Player::instanceFlag = false;
Player* Player::player = NULL;

Player* Player::getInstance()
{   //!Creates a new player then returns player.
	if(!instanceFlag)
	{
		player = new Player();
		instanceFlag = true;
		return player;
	}
	//! Returns the player if there is already a player.
	else return player;
}
void Player::Initialise()
{
	texture = LoadTexture::getInstance();
	box.setSize(32,32);
	box.setPos(circle.getPosition());
	box.setTextureCoords(11*16,22*16);
	Vector2D acc(0,0);//!< Acc is 9.81 in Y.
	circle.setParams(15.f,20,circle.getPosition().getX(),circle.getPosition().getY());//!< Radius, Number of points, Position
	circle.setCoeffient(0.0f,0.2f,0.1f,0.f);//!< Drag, Density, Elasticity, Friction*  *friction doesnt work.
	circle.setAcc(acc);//!<Sets the acceleration to player.
	animate.Initialise(Vector2D(17,22),Vector2D(15,22),120.f,&box);
	right = false;
	left = false;
}
void Player::Update(float time)
{
	circle.Update(time);//!< Integration with the player.#
	box.setPos(circle.getPosition());

}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	//target.draw(circle);
	target.draw(box,texture->getTexture());//!< Draws the circle.
}
Circle * Player::getPlayer()
{
	return &circle;//!< Returns adderess of the circle.
}
void Player::AnimateRight()
{
	if(!right)
	{
		animate.Initialise(Vector2D(15,22),Vector2D(17,22),120.f,&box);
		right = true;
		left = false;
	}
	animate.Update();//!< Updates the animation
}
void Player::AnimateLeft()
{
	if(!left)
	{
		animate.Initialise(Vector2D(15,25),Vector2D(17,25),120.f,&box);
		left = true;
		right = false;
	}
	animate.Update();//!< Updates the animation
}
void Player::setStill()
{
	left=false;
	right = false;
	box.setTextureCoords(21*16,22*16);//!< Sets the texture to Still texture.
}
void Player::setJumping()
{
	left=false;
	right = false;
	box.setTextureCoords(19*16,22*16);//!< Sets the texture to jumping texture.
}
void Player::setDead()
{
	box.setTextureCoords(20*16,22*16);//!< Sets the texture to Death.
}
void Player::setSpeed(float nSpeed)
{
	animate.setSpeed(nSpeed);//!<Sets the speed of the animation.Lower speed is faster
}