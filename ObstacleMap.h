#ifndef OBSTACLEMAP_H
#define OBSTACLEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Box.h"
#include "LoadTexture.h"
#include "Enemy.h"
#include <list>
#include "Coin.h"
#include "Player.h"
/*! \brief Loads in the map collisions player position. Enemies and coins.  */
class ObstacleMap: public sf::Drawable
{
private:
	int height;//!< Height of map.
	int width;//!< width of map.
	int gridSquareSize;//!< size of each square in the map
	std::vector<std::vector<Box>> drawMap;//!< Holds the map that only draws objects.
	//sf::Color colour;
	Box box;//!< Box that creates all of the map.
	Player* player;//!< pointer to player.
	LoadTexture* texture;//!< pointer to texture
	Enemy enemy;//!< create and enemy object.
	Coin coin;//!< create a coin object
	std::list<Coin> coins;//!< list of coin.
	std::list<Enemy> enemies;//!< list of enemy
	std::vector<std::vector<Box>> colsMap;//!< Holds all the blocks that are dynamic
public:
	
	ObstacleMap();//!< default constructor
	~ObstacleMap();//!< default decnostructor
	void loadFromFile(const char * fileName);//!< loads the map.
	
	void setTextureCoords(int nx, int ny);//!< use to set the texture coors for some collidable boxes.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;//!< draw function
	std::vector<std::vector<Box>> * getMap();//!< returns a pointer to the Drawmap
	std::vector<std::vector<Box>> * getCollisions();//!< returns a pointer to the collision map
	std::list<Enemy> * getEnemies();//!< returns a poiinter to the enemylist
	std::list<Coin> * getCoins();//!< returns a pointer to the coin list.


};



#endif