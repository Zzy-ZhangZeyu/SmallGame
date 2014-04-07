#ifndef BOX_H
#define BOX_H
#include <SFML\Graphics.hpp>
#include "Vector2D.h"
#include "Moveable.h"
#include <iostream>
#include "LoadTexture.h"
/*! \brief Creates a box that has texture coordinates and is used for maps collision maps and drawing Sprites.*/
class Box: public sf::Drawable, public Moveable
{
	
private:
	float height, width;//!< Height and the Width of the Box
	sf::VertexArray rect;//!< Define the Box.
	float inverseMass;//!< inverseMass of the box. used in collision when 0. doesnt move.
	bool destroyable;//!< Set true if can be destroyed
	bool questionMark;//!< Set true if its a ?


public:
	Box();//!<Default constructor
	~Box();//!< Deconstructor
	Box(float &nheight, float &nWidth);//!< Constructor with height and width
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;//!<Draw the box
	void setSize(float nheight, float nWidth);//!< Function that sets the size
	float getHeight()const;//!< Returns the height
	float getWidth()const;//!< Returns the width
	void setPos(float xPos, float yPos);//!< Sets the position of the box
	void setPos(Vector2D nPos);//!< Sets the position of the box using Vector2D
	void setInverseMass(float nInverseMass);//!< Sets the inverseMass. if you want immoveable set to 0;
	float getInverseMass()const;//!< Returns the inverse mass
	void Update(float time);//!< Rk4 integration
	Vector2D getPosition()const;//!Returns position
	void setTextureCoords(float nx, float ny);//!< Sets the texture coords.
	void setTextureCoords(float nx, float ny, float nwidth, float nheight);
	void setParams(Vector2D pos, Vector2D TexCoord, Vector2D size);//!< Sets all params in one function.
	void setDestroyable(bool b);//!< Sets if can be destroyed.
	void setQuestionBlock(bool b);//!< Sets if is a ? block. (has coin in it)
	bool getQuestionBlock()const;//!< Returns value of ? bool.
	bool getDestroyable()const;//!< Returns if can be destroyed.
};

#endif