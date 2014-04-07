#ifndef ANIMATE_H
#define ANIMATE_H

#include "LoadTexture.h"
#include "Vector2D.h"
#include <SFML\System\Clock.hpp>
#include "Box.h"

/*! \brief Class that is used for animating objects. */
class Animate
{
private:
	unsigned int startRow, endRow;//!< Start and end Rows.
	unsigned int col,row;//!< Temp values.
	unsigned int startColumn, endColumn;//!< Start and end columns
	float speed;//!< Speed which it updates.
	Vector2D startPos;//!< Start Pos
	Vector2D endPos;//!< End pos.
	Box* box;//!< Pointer to the box.
	sf::Clock clock;
	//sf::Time time;
	float time;
public:
	Animate();
	Animate(Vector2D NstartPos, Vector2D NendPos, float Nspeed, Box* nBox);//!< Initialises. In constructor.
	void Initialise(Vector2D NstartPos, Vector2D NendPos, float Nspeed, Box* nBox);//!< Initialises.
	void Update(Box* nBox);//!< Updates. 
	void Update();//!< Updates
	void Reset();//!< Resets starts to 0;
	void setSpeed(float nSpeed);//!< sets the speed the Update.
};
#endif