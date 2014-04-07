#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include "Vector2D.h"
#include "Circle.h"
#include "Box.h"
#include "LoadTexture.h"
#include "Animate.h"
/*! \brief Creates the player*/
class Player: public sf::Drawable
{
	//! Implements a Singleton Class
private:
	Circle circle;//!< Defines the player as a circle
	Box box;
	Animate animate;
	bool right;
	bool left;
	LoadTexture* texture;
	static bool instanceFlag;//!< Creates a bool. Thats allows me to check if a new player has been made.
	static Player *player;//!< Creates a pointer of player.
	Player()
	{}
public:
	~Player()
	{
		instanceFlag = false;
	}

	static Player* getInstance();//!< Returns the player class. Creates a new player if. There isn't one.
	void Initialise();//!< Initialises stuff for player.
	void Update(float time);//!< Updates the player.
	void AnimateRight();//!< Animates Right
	void AnimateLeft();//!< Animates Left
	void setSpeed(float nSpeed);//!<Sets animation speed. Lower is faster
	void setStill();//!< Sets texture to still 
	void setJumping();//!< Sets texture to jumping
	void setDead();//!< Sets texture to dead
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;//!< Draws the player
	Circle * getPlayer();//!< Returns the circles
};


#endif