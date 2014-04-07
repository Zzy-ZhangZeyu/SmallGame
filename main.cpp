/*! \mainpage Dave the plumber
*
*Hello Simon. Remember please turn the sound on and i hope you enjoy the game. 
*
*Left and Right arrows to move.
*
*Space to jump.
*
*Hold X to Run faster.
*
*P in the level file will set the start position of the player. If you choose to start at the end of level one.
*
*Once you completed a level the next level loads once the music has ended.
*/

#include "Game.h"

int main()
{
	Game game;
	game.Run();
	return 0;
};