#ifndef ENEMY_H
#define ENEMY_H
#include <SFML\Graphics.hpp>
#include "Box.h"
#include "Animate.h"
#include "LoadTexture.h"
/*! \brief Creates an enemy.*/ 
class Enemy: public sf::Drawable
{
private:
	LoadTexture* texture;
	Box box;//!< Creates the enemy box.
	bool initialised;//!< Initiates initial velocity. then sets to false.
	Animate animate;
public:
	Enemy();//!< Default constructor.
	~Enemy();
	void Initialise(float height, float width, float xPos, float yPos);//!< Initialises parameters for the Enemy
	void Update(float time);//!< Integration Rk4 and Update animation
	bool getInitialised(){return initialised;};//!< Returns a bool
	void setInitialised(bool nIn){initialised = nIn;};//!< Sets a bool
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;//!< Draws the Enemy
	Box * getEnemy();//!<Returns the box;
};
#endif