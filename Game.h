#ifndef GAME_H
#define GAME_H


#include "Vector2D.h"
#include "Circle.h"
#include "Box.h"
#include "Collision.h"
#include "ObstacleMap.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "Animate.h"
#include <SFML\Audio\Music.hpp>

#define REFRESH_RATE 0.00833f

enum GameState {Menu, Running, Paused, GameOver, Winner};
/*! \brief Iterates through all Collisions. Changes GameStates. Sets View.*/
class Game
{
private:
	void Initialise();//!< Initialises the game.
	void ProcessEvents();//!< Processes the game events
	void Update();//!< Updates the game
	void Render();//!< Renders to the screen.
	
private:
	float centre;//!< Centre of the view.
	float zoom;//!<Amount zoomed in by view.
	float newPos;//!< New position for View.
	bool played;//!< Boolean to tell when music is played
	bool levelLoaded;//!< Boolean to tell when the level has been loaded.
	bool jumped;//!< Boolean to tell when the player as jumped.
	bool isOn;//!< Toggle thats used for pause and view collision checks.
	bool viewCol;//!< View Collision checks if truel
	bool enemyDelete;//!< Deletes enemy if true;
	bool hitEnemy;//!<Boolean to tell if hit an enemy on the top.
	bool hitFloor, hitSide, hitUnder;//!< Boolean to tell if hit blocks on top, side and under.
	
	float gravity;//!< Value of gravity.
	sf::View view;//!< view used to zoom and follow player.
	float maxVel;//!< Max vel the player can move.
	GameState gamestate;//!< The state the game is in.
	sf::Clock clock, nClock;//!< clock is for Timestep, nClock is for jump time.

	//! See Winner case under UPDATE.
	int level;//!< Variable used to tell what level im on. Goes into the String stream.
	std::stringstream ss;//!<Used when changing level. In winner case. Converting string to char.

	//! These ints are used for finding the position of the boxes that need to be checked for collision
	int checkDistanceX, checkDistanceY;//!< Distance that collisions are checked.
	int PposPlus;
	int PposMinus;
	int PposPlusY;
	int PposMinusY;
	int EposPlusX;
	int EposMinusX;
	int EposPlusY;
	int EposMinusY;

	LoadTexture* texture;//!< Pointer to the sprite sheet.
	Text menuPlayer, exit;//!< Text on Title screen.
	Coin aniCoin;//!< animation coin.
	std::vector<Coin>::iterator aniCoinIt;//!< Iterator of coins.
	std::vector<Coin> aniCoins;//!< Vector of coins that animate.

	UI ui;//!< UI, Time coins and score.
	
	Box menuDisplay, menuSelector;//!< Mario Bro's Sign on title page and the cloud selector.
	Box emp;//!<Empty box that gets replaced instead of deleting from map.
	Box bBox;//!< A box that is left of the view that the player collides with.
	Box detectionBox;//!< A box that is infront of the view that initiates the enemies.

	std::list<Coin>::iterator cIt;//!< Iterator of coins.
	std::list<Enemy>::iterator enemiesIt;//!< Iterator of enemies.
	ObstacleMap map;//!< Used to get Vectors from map and draw the map.
	Collision collision;//!< Used to check collisions
	Player *player;//!< pointer to player.
	sf::RenderWindow mWindow;//!< Window.
	sf::Music music,gMusic, winMusic, titleMusic;//!< All the music.

	std::vector<std::vector<Box>>::iterator boxIt;//!< Iterator of map in X.
	std::vector<Box>::iterator boxIt2;//!<Iterator of map in Y
	
public:

	Game();//!< Default constructor that calls initialise function.
	~Game();
	void Run();//!< Runs the game. Calls the Update and Render.
	void PlayerInput();//!< Deals with player Input.
	void CheckCollision();

};
#endif