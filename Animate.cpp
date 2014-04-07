/*!
@Animate.cpp
*/

#include "Animate.h"

Animate::Animate(){}

Animate::Animate(Vector2D NstartPos, Vector2D NendPos, float Nspeed, Box* nBox)
{
	startColumn = (int)NstartPos.getX();
	startRow = (int)NstartPos.getY();
	endColumn = (int)NendPos.getX()+1;
	endRow = (int)NendPos.getY();
	box = nBox;
	speed = Nspeed;
	col = startColumn;
	row = startRow;
}
void Animate::Initialise(Vector2D NstartPos, Vector2D NendPos, float Nspeed, Box* nBox)
{
	startColumn = (int)NstartPos.getX();
	startRow = (int)NstartPos.getY();
	endColumn = (int)NendPos.getX()+1;
	endRow = (int)NendPos.getY();
	box = nBox;
	speed = Nspeed;
	col = startColumn;
	row = startRow;
}

void Animate::Update()
{
	
	time = (float)clock.getElapsedTime().asMilliseconds();
	//! Updates col and row after certain time.
	if(time > speed)
	{
		++col;
		time = 0.f;
		if(col == endColumn)
		{
			col = startColumn;
			if(row != endRow)
			{
				++row;
			}
			
		}
		clock.restart();
	}
	
	box->setTextureCoords(col*16,row*16);//!< SEts texture Coordinates of the box.

}
void Animate::Update(Box* nBox)
{
	box = nBox;
	time = (float)clock.getElapsedTime().asMilliseconds();
	//! Updates col and row after certain time.
	if(time > speed)
	{
		++col;
		time = 0.f;
		if(col == endColumn)
		{
			col = startColumn;
			if(row != endRow)
			{
				++row;
			}
			
		}
		clock.restart();
	}
	//
	box->setTextureCoords(col*16,row*16);//!< SEts texture Coordinates of the box.
	
}
void Animate::Reset()
{
	startColumn = 0;//!<REsets to 0
	startRow =  0; //!<REsets to 0
}

void Animate::setSpeed(float nSpeed)
{
	speed = nSpeed;//!< SEts the speed of the animation. Lower is faster.
}