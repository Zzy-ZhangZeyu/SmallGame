/*!
@ObstacleMap.cpp
*/

#include "ObstacleMap.h"


using namespace std;

ObstacleMap::ObstacleMap()
{
	height = 0;
	width = 0;
	gridSquareSize = 0;
	texture = LoadTexture::getInstance();
	player = Player::getInstance();
	//texture->Initialise();

}
ObstacleMap::~ObstacleMap()
{
}


void ObstacleMap::loadFromFile(const char * fileName)
{
	ifstream inputFile;
	istringstream parser;
	string line;
	char character;
	int numberFromFile;

	inputFile.open(fileName);//!< Opens the file
	if(inputFile.is_open())//!< If the file is open
	{

		int enemyQuantity;

		getline(inputFile,line);
		parser.clear();
		parser.str(line);
		parser >> height >> width >> gridSquareSize;//!< Read in height and width of Map. Then the size of each square.
		drawMap.resize(width);
		for(int i=0;i<width;++i)
		{
			drawMap[i].resize(height);
		}
		colsMap.resize(width);
		for(int i=0;i<width;++i)
		{
			colsMap[i].resize(height);
		}
		box.setSize(gridSquareSize,gridSquareSize);

		int j = 0;
		while ( getline(inputFile,line) ) 
		{
			int i = 0;
			// Send the string reader to have our newly read line
			parser.clear();
			parser.str(line);
			// Read all the numbers
			while(parser >> character)
			{
				
				switch(character)
				{
				case '1':
					box.setQuestionBlock(false);
					box.setDestroyable(true);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);//!<Sets the position of the texture.
					box.setTextureCoords(0*16,0);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '2':
					box.setQuestionBlock(true);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(24*16,0);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '3':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(0*16,9*16);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '4':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(1*16,9*16);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '5':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(0*16,8*16);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '6':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(1*16,8*16);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '7':
					box.setQuestionBlock(false);
					box.setDestroyable(true);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(2*16,0*16);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case 'n':
					box.setQuestionBlock(true);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(2*16,0*16);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '8':
					box.setQuestionBlock(false);
					box.setDestroyable(true);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(1*16,0);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '9':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(0*16,16);
					box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					box.setInverseMass(0);
					colsMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case 'o':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(16*16,8*16);
					//box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					//box.setInverseMass(0);
					drawMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '|':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(16*16,9*16);
					//box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					//box.setInverseMass(0);
					drawMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '/':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(8*16,8*16);
					//box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					//box.setInverseMass(0);
					drawMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '\\'://!< Single Backslash escapes quote
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(10*16,8*16);
					//box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					//box.setInverseMass(0);
					drawMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '[':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(10*16,9*16);
					//box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					//box.setInverseMass(0);
					drawMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case ']':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(8*16,9*16);
					//box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					//box.setInverseMass(0);
					drawMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case '^':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(9*16,8*16);
					//box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					//box.setInverseMass(0);
					drawMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case 'h':
					box.setQuestionBlock(false);
					box.setDestroyable(false);
					box.setPos(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					box.setTextureCoords(9*16,9*16);
					//box.setCoeffient(0.05f,6.f,1.0f,0.0f);
					//box.setInverseMass(0);
					drawMap[i][j] = box;//!< Pushes a box into a vector of boxes
					break;
				case 'e':
					enemy.Initialise(gridSquareSize,gridSquareSize,
						i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					enemies.push_back(enemy);
					break;
				case 'c':
					coin.Initialise(gridSquareSize,gridSquareSize,
						i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2);
					coins.push_back(coin);
					break;
				case 'p':
					player->getPlayer()->setPos(Vector2D(i*gridSquareSize+gridSquareSize/2,j*gridSquareSize+gridSquareSize/2));
					break;
				default:
					break;
				}

				//if(character == 'e')
				//{
				//	//!< Pushes a box into a vector of boxes
				//}
				++i;
			}
			++j;

		}
		inputFile.close();
	}

}
void ObstacleMap::setTextureCoords(int nx, int ny)
{
	box.setTextureCoords(nx,ny);//!< Set the texture coordinate for the collidable box.
}

void ObstacleMap::draw(sf::RenderTarget &target, sf::RenderStates states)const
{

	//box.setTextureCoords();
	std::vector<std::vector<Box>>::const_iterator it;
	std::vector<Box>::const_iterator it2;
	//states.texture = ;
	
	for(it = colsMap.begin(); it != colsMap.end(); ++it)
	{
		
		for(it2 = it->begin();it2 != it->end();++it2)
		{
			//!Draws Collidable boxes
			it2->draw(target,texture->getTexture());

		}
		
	}
	
	for(it = drawMap.begin(); it != drawMap.end(); ++it)
	{
		
		for(it2 = it->begin();it2 != it->end();++it2)
		{
			//!Draws none collidable boxes
			it2->draw(target,texture->getTexture());

		}
		
	}
	
}

std::vector<std::vector<Box>> * ObstacleMap::getMap()
{
	return &drawMap; //!< Returns the draw map
}
std::vector<std::vector<Box>> * ObstacleMap::getCollisions()
{
	return &colsMap;//!< Returns the collision map.
}
std::list<Enemy> * ObstacleMap::getEnemies()
{
	return &enemies;//!< Returns the list of enemies.
}
std::list<Coin> * ObstacleMap::getCoins()
{
	return &coins;//!< Returns the list of coins.
}


