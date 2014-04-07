/*!
@Game.cpp
*/

#include "Game.h"

Game::Game()
{
	Initialise();
}
Game::~Game()
{
}

void Game::Run()
{
	//! run the program as long as the window is open
	while(mWindow.isOpen())
	{

		ProcessEvents();//!< Constantly Processes events.
		//!Updates the game withing the Refresh Rate.
		if((float)clock.getElapsedTime().asSeconds() > REFRESH_RATE)
		{	
			Update();
			clock.restart();
		}

		Render();//!< Constantly renders the game

	}

}

void Game::Initialise()
{
	//!Creates the window
	mWindow.create(sf::VideoMode(1024,768), "Dave Game");//!< Creates the window.
	map.loadFromFile("Level1.txt");//!< Loads the first level.
	level = 1;
	gravity = 9.81f;//!< Value of gravity.
	Vector2D acc(0,gravity);//!< SEts the gravity into a vector/
	if(!gMusic.openFromFile("./Music/GameOver.ogg"))
	{
		std::cout << "Failed/n";
	}
	if(!music.openFromFile("./Music/OverWorld.ogg"))
	{
		std::cout << "Failed/n";
	}
	music.setVolume(100);
	music.setLoop(true);
	if(!winMusic.openFromFile("./Music/CourseClear.ogg"))
	{
		std::cout << "Failed/n";
	}
	if(!titleMusic.openFromFile("./Music/Title.ogg"))
	{
		std::cout << "Failed/n";
	}
	titleMusic.setLoop(true);


	texture = LoadTexture::getInstance();//!< sets texture to texture.
	player = Player::getInstance();//!< sets player to the player.
	player->Initialise();//!< Initialises the player.

	zoom = 0.6f;//!< Amount the view zooms in.
	centre = 768.f/2.f;//!< Sets the view centre.
	newPos = 768.f - (centre * zoom) ; //!< Calculates the camera depending on how much is zoomed.
	view.setSize(sf::Vector2f(1024,768));
	view.setCenter(sf::Vector2f(384,newPos));//!< Sets the initial pos of the camera.
	view.zoom(zoom);//!< Zoom in on the screen.
	ui.Initialise(view);

	enemyDelete = false;//!< Bool to tell when to delete the enemy.
	isOn  = false;//!< Used to toogle the checking collision box render.
	hitEnemy=false;//!< Bool to tell if hit an enemy
	hitFloor=false;//!< Bool to tell whether hit the floor.
	hitUnder=false;//!< Bool to tell whether Hit under a block.
	hitSide=false;//!< Bool to tell hit the side of a block or enemy.
	viewCol=false;//!< Bool to view the Collision boxes.
	jumped=false;//!< Bool to tell if the player has jumped.
	levelLoaded = true;//!< Level has been loaded.
	checkDistanceX = 2;//!< Collision check distance in X.
	checkDistanceY = 2;//!< Collision check distance in Y.
	maxVel = 20.f;//!< Sets the velocity.


	bBox.setSize(768,32);//!< A box that is left of the view that the player collides with.
	bBox.setCoeffient(0.f,1.5f,1.f,0.f);
	bBox.setInverseMass(0);
	detectionBox.setSize(768,10);//!< A box that is infront of the view that initiates the enemies.
	detectionBox.setCoeffient(0.f,1.5f,1.f,0.f);
	detectionBox.setInverseMass(0);
	menuSelector.setSize(16,16);
	menuSelector.setPos(view.getCenter().x - 100.f, view.getCenter().y+58.f);
	gamestate = Menu;//!< Start game in Menu state.

}


void Game::ProcessEvents()
{

	//! check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		//! "close requested" event: we close the window

		switch(event.type)
		{
		case sf::Event::KeyPressed://!< Event to tell if a key has been pressed.
			//! Toggles viewing collisions checked.
			if(event.key.code == sf::Keyboard::D)
			{
				isOn = !isOn;
				if(isOn)
				{
					viewCol = true;
				}
				else viewCol = false;
			}
			//! Toggles pause.
			if(event.key.code == sf::Keyboard::P && gamestate == Running || event.key.code == sf::Keyboard::P && gamestate == Paused)
			{
				isOn = !isOn; 
				if(isOn)
				{
					gamestate = Paused;
				}
				else gamestate = Running;
			}

			break;
		case sf::Event::KeyReleased://!< Event to tell when key has been released
			//!When left or right key is released and mario is on then floor. mario will stop.
			if(event.key.code == sf::Keyboard::Left && hitFloor && gamestate == Running || event.key.code == sf::Keyboard::Right && hitFloor && gamestate == Running)
			{
				player->setStill();
				player->getPlayer()->setAcc(Vector2D(0,gravity));
				player->getPlayer()->setVel(Vector2D(0,player->getPlayer()->getVelocity().getY()));
			}
			
			break;
		case sf::Event::Closed://!< Event to close the window.
			mWindow.close();//!< Closes the window. When clicked close button.
		default:
			break;
		}
	}
	
	PlayerInput();//!< Holds movement.

}
void Game::Update()//!< Updates the phyics and the collisions.
{
	
	switch(gamestate)
	{
	case Menu:
		//!Play title music.
		if(titleMusic.getStatus() != titleMusic.Playing)
		{
			titleMusic.play();
		}
		played = false;//!< Sets if Winner and GameOver music has been played to false.
		level = 1;
		//! Moves the Selector on the menue/
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			menuSelector.setPos(view.getCenter().x - 100.f, view.getCenter().y+58.f);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			menuSelector.setPos(view.getCenter().x - 100.f, view.getCenter().y+88.f);
		}
		//! If the level hasnt been loaded then load the level.
		if(!levelLoaded)
		{
			map.getEnemies()->clear();//!<Clears the enemies
			map.getCoins()->clear();//!<Clears the coins
			map.getMap()->clear();//!<Clears the map
			map.getCollisions()->clear();//!< Clears collision map.
			map.loadFromFile("Level1.txt");//!<Reloads the map
			levelLoaded = true;//!<Map has been reloaded.
		}
		ui.Reset(view);//!<Resets the UI
		player->setStill();//!< Set to still texture.
		player->getPlayer()->setVel(Vector2D(0.f,0.f));//!<resets the velocity.
		player->getPlayer()->setAcc(Vector2D(0.f,gravity));//!<resets the Acceleration.
		view.setCenter(sf::Vector2f(384,newPos));//!< Sets the initial pos of the camera.

		menuSelector.setTextureCoords(4*16,21*16);//!< Sets texture coords of the selector.

		menuDisplay.setSize(88.f*2.5f,176.f*2.5f);//!< Sets the Size of the mario bros display.
		menuDisplay.setPos(view.getCenter().x,view.getCenter().y - 75.f);//!< Sets the Position of the mario bros display
		menuDisplay.setTextureCoords(22*16,22*16,176.f,88.f);//!< sets the texture coordinates of it.

		menuPlayer.setPosition(view.getCenter().x - 80.f, view.getCenter().y+50.f);//!< Sets the Position of 1 Player Game.
		menuPlayer.setString("1 PLAYER GAME");//!< Sets the string.

		exit.setPosition(view.getCenter().x - 80.f, view.getCenter().y+80.f);//!< sets the position of exit.
		exit.setString("EXIT");//!< sets the string to Exit.

		//! Gets the position of the menu selector and changes states if pressed return.
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&& menuSelector.getPosition().getY() == view.getCenter().y+58.f)
		{
			gamestate = Running;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&& menuSelector.getPosition().getY() == view.getCenter().y+88.f)
		{
			mWindow.close();
		}
		break;
	case Running:
		played = false;//!< Sets if Winner and GameOver music has been played to false.
		titleMusic.stop();//!< Stop the title Music
		//! If Music isnt playing the play the music.
		if(music.getStatus() != music.Playing)
		{
			music.play();
		}

		//!Time reaches 0 game over.
		if(ui.getTime() == 0)
		{
			gamestate  = GameOver;
		}
		ui.Update(view, REFRESH_RATE);//!< Update the UI
		//view.setSize(sf::Vector2f(1024,768));//!< reset the view size. So zoom doesn't continously happen.
		//! If the player goes past the screen. Move the screen with the player.
		if(player->getPlayer()->getPosition().getX() > view.getCenter().x )
		{
			view.setCenter(sf::Vector2f(player->getPlayer()->getPosition().getX(), newPos));
		}
		

		bBox.setPos((view.getCenter().x - (view.getSize().x/2)/**zoom*/)-16,newPos);//!< Updates the Position of the box on the left.
		detectionBox.setPos((view.getCenter().x + (view.getSize().x/2)*zoom + 150),newPos);//!<Sets Pos of detection box.
		//view.zoom(zoom);//!< Zoom in on the screen.

		//! If the player falls of the level then its game over.
		if(player->getPlayer()->getPosition().getY() > 768.f+16.f)
		{
			gamestate = GameOver;
		}

		//! If the player reaches the end then its game over.
		if((int)player->getPlayer()->getPosition().getX()/32 == 198)
		{
			player->getPlayer()->setAcc(Vector2D(0,0));
			player->getPlayer()->setVel(Vector2D(0,0));
			gamestate = Winner;
		}

		//! If the player reaches the end stop the view.
		if((int)player->getPlayer()->getPosition().getX()/32 >= 194)
		{
			view.setCenter(sf::Vector2f(194*32, newPos));
		}


		
		CheckCollision();//!<Iterates through collisions
		

		//!<Updates Moving Coins
		for(aniCoinIt = aniCoins.begin(); aniCoinIt != aniCoins.end();/*++aniCoinIt*/ )
		{
			aniCoinIt->Update(REFRESH_RATE);
			if(aniCoinIt->getCoin()->getPosition().getY() < aniCoinIt->getStartPos().getY() -100.f)
			{
				aniCoinIt = aniCoins.erase(aniCoinIt);
			}
			else ++aniCoinIt;
		}
		//!Updates the coins
		for(cIt = map.getCoins()->begin(); cIt != map.getCoins()->end();++cIt)
		{
			cIt->Update(REFRESH_RATE);
		}

		//!Updates the enemies
		for(enemiesIt = map.getEnemies()->begin(); enemiesIt != map.getEnemies()->end();++enemiesIt)
		{
			enemiesIt->Update(REFRESH_RATE);
		}

		
		player->Update(REFRESH_RATE);//!< Update the player.
		

		break;

	case Paused://!< Stops Updating
		//! Displays Paused
		menuPlayer.setPosition(view.getCenter().x -45.f, view.getCenter().y);
		menuPlayer.setString("PAUSED");
		music.pause();//!< Pauses the music.

		break;
	case GameOver:
		music.stop();//!< Stops the running music.

		if(!played)//!< If gameover music isnt playing.
		{
			player->setDead();//!< set dead.
			gMusic.play();//!< Play gameover music.
			played = true;//!< Set to true.
		}
		menuPlayer.setString("GAME OVER");
		menuPlayer.setPosition(view.getCenter().x -45.f, view.getCenter().y);

		levelLoaded = false;//!< Level is no longer loaded

		if(gMusic.getStatus() == gMusic.Stopped)//!< Once the music has stopped. 
		{
			gamestate = Menu;//!< return to menu
			break;
		}

		break;

	case Winner:

		music.stop();//!< Stop running music
		if(!played)//!< If winner music isnt playing.
		{
			++level;//!< Increase the level
			menuPlayer.setPosition(view.getCenter().x -120.f, view.getCenter().y);
			menuPlayer.setString("LEVEL COMPLETED");//!< Display Level Completed.
			ui.AddtoScore(2000);//!< Add 2000 for completing the level.
			winMusic.play();//!< Play winnders music
			played = true;//!< Played is now true
		}
		//! Add remaining time to the score and deduct from time.
		for(int i = 0; i < ui.getTime();++i)
		{
			ui.AddtoScore(1);
			ui.setTime(ui.getTime()-1);
		}
		ui.Update(view,REFRESH_RATE);//!< Update view.

		if(winMusic.getStatus() == winMusic.Stopped)//!< If the music has finished
		{
			//! If the level is 3. Reset to level 1 and return to menu. early.
			if (level == 3)
			{
				level = 1;
				gamestate = Menu;
				levelLoaded = false;
				break;
			}

			ss.str("");//!< Clear string
			ss << "Level" << level << ".txt";//!< create string
			std::string tmp = ss.str();//!< Change tmp string to string stream string
			const char* l = tmp.c_str();//!< convert the tmp string into a char string.
			player->getPlayer()->setAcc(Vector2D(0.f,gravity));//!< set the acc of the player.
			map.getEnemies()->clear();//!<Clears the enemies
			map.getCoins()->clear();//!<Clears the coins
			map.getMap()->clear();//!<Clears the map
			map.getCollisions()->clear();//!< Clears collision map.
			map.loadFromFile(l);//!< Load the next map.
			view.setCenter(sf::Vector2f(384,newPos));//!< Sets the initial pos of the camera.
			ui.setTime(300);//!< Reset time to 300;
			gamestate = Running;//!< start the level.
		}

		break;
	}


}
void Game::Render()//!< Renders the scene
{
	mWindow.clear(sf::Color(43,111,213,255));//!< Clears the screen.
	mWindow.setView(view);//!< Set the view.
	//!Draw here
	switch(gamestate)
	{
	case Menu:

		
		mWindow.draw(map);//!< Draw the level
		mWindow.draw(menuPlayer);//!< Draw the 1 Player Game
		mWindow.draw(exit);//!< Draw the exit.
		mWindow.draw(menuSelector,texture->getTexture());//!< Draw the menu selector
		mWindow.draw(menuDisplay,texture->getTexture());//!< Draw the Mario Bro sign
		break;
	case Running: case Paused: case GameOver: case Winner://!< If its in any of these cases then draw...

		//!Draw the coins that moves.
		for(aniCoinIt = aniCoins.begin(); aniCoinIt != aniCoins.end(); ++aniCoinIt)
		{
			mWindow.draw(*aniCoinIt);
		}
		//!Draws the level.
		mWindow.draw(map);
		//!Draws the coins
		for(cIt = map.getCoins()->begin(); cIt != map.getCoins()->end();++cIt)
			mWindow.draw(*cIt);
		//! Draws the enemies.
		for(enemiesIt = map.getEnemies()->begin(); enemiesIt != map.getEnemies()->end();++enemiesIt)
			mWindow.draw(*enemiesIt);
		//!Draws the boxes that the player and enemy is checking collision with.
		if(viewCol)
		{
			for(boxIt = map.getCollisions()->begin()+PposMinus; boxIt != map.getCollisions()->begin()+PposPlus;++boxIt)
			{
				for(boxIt2 = boxIt->begin()+PposMinusY; boxIt2 != boxIt->begin()+PposPlusY;++boxIt2)
				{
					mWindow.draw(*boxIt2);
					//hitSide=false;
				}
			}
		}
		//mWindow.draw(bBox);

		mWindow.draw(*player);//!< Draws the player.

		if(gamestate == Paused)
		{
			mWindow.draw(menuPlayer);//!< Draw PAUSED if in the pause state.
		}
		else if(gamestate == GameOver)
		{
			mWindow.draw(menuPlayer);//!< Draw GAMEOVER if in the gameover state.
		}
		else if(gamestate == Winner)
		{
			mWindow.draw(menuPlayer);//!< Draw level Completed if in the winner state.
		}

		break;



	}
	mWindow.draw(ui);//!< Draw the ui.
	mWindow.display();//!< Display to screen/
}
void Game::PlayerInput()
{
	switch(gamestate){
	case Running:
		//! If mario isnt jumping use first movement. else If he has jumped. Use bottom movement
		if(!jumped)
		{
			nClock.restart();//!< Restart the jump clock.
			//! Run left.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& player->getPlayer()->getVelocity().getY() < 0.5f)
			{
				player->AnimateLeft();
				player->getPlayer()->setAcc(Vector2D(-maxVel,gravity));
			}
			//! Run right
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& player->getPlayer()->getVelocity().getY() < 0.5f)
			{
				player->AnimateRight();
				player->getPlayer()->setAcc(Vector2D(maxVel,gravity));
			}
			//! Speed up
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				player->setSpeed(50.f);//!< Speed up animation
				maxVel = 50.f;//!< Change Velocity.
			}else {
				maxVel = 20.f;//!< Change to normal Velocity.
				player->setSpeed(120.f);//!< Change to normal animation
			}
		}
		else{
			//!< Travel left if in air
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& player->getPlayer()->getVelocity().getY() < 0.5f)
			{
				player->setJumping();
				player->getPlayer()->setAcc(Vector2D(-maxVel*0.9,gravity+35));
			}
			//!< Travel right if in air
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& player->getPlayer()->getVelocity().getY() < 0.5f)
			{
				player->setJumping();
				player->getPlayer()->setAcc(Vector2D(maxVel*0.9,gravity+35));
			}


		}
		//! If mario walks off ledge Change the gravity. else if he hits the floor change it back.
		if(hitFloor && player->getPlayer()->getVelocity().getY() > 5.5f)
		{
			player->getPlayer()->setAcc(Vector2D(player->getPlayer()->getAccel().getX(),gravity+35));
		}
		else if(hitFloor) player->getPlayer()->setAcc(Vector2D(player->getPlayer()->getAccel().getX(),gravity));

		//! If mario jumped then hit the floor. reset Texture coords and gravity.
		if(jumped && hitFloor)
		{
			player->getPlayer()->setAcc(Vector2D(player->getPlayer()->getAccel().getX(),gravity));
			player->setStill();
			jumped = false;

		}
		//! Can jump when velocity in Y is less that 0.5 and if the timer is less than 0.3 seconds.
		//! This jumping method can prove a little problematic as in debug it doesn't run at refresh rate.
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& player->getPlayer()->getVelocity().getY() < 0.5f && nClock.getElapsedTime().asSeconds() < 0.3f )
		{
			hitFloor = false;
			jumped = true;
			player->setJumping();
			player->getPlayer()->setAcc(Vector2D(0,gravity+35));
			player->getPlayer()->setVel(Vector2D(player->getPlayer()->getVelocity().getX(),-60));
		}
		
		//!If the velocty reaches max vel then cap it at the max Vel.
		if(player->getPlayer()->getVelocity().getX() < -maxVel)
		{
			player->getPlayer()->setVel(Vector2D(-maxVel ,player->getPlayer()->getVelocity().getY()));
		}
		if(player->getPlayer()->getVelocity().getX() > maxVel)
		{
			player->getPlayer()->setVel(Vector2D(maxVel ,player->getPlayer()->getVelocity().getY()));
		}
		
	
		break;
	}


}
void Game::CheckCollision()
{
	Vector2D normal;//< Holds the normal. 
	//const sf::FloatRect rect(0,0,1,1);//!<
for(int i=0; i<2;++i)//!< Iterate through collisions a couple of times.
		{
			//! If players falls off edge the reset back to start.

			//!Checks collision between the player and box behind the player.
			if(collision.CircleToAABB(*player->getPlayer(),bBox,hitFloor,hitSide,hitUnder))
			{
				collision.applyCtoAABBimpulse(*player->getPlayer(),bBox);
				hitSide = false;
				hitFloor = false;
				hitUnder = false;
			}
			//!gets player grid pos and + or -  to check collision around it. 

			checkDistanceX = 2;
			checkDistanceY = 2;
			PposPlus = (int)player->getPlayer()->getPosition().getX()/32 + checkDistanceX;
			PposMinus = (int)player->getPlayer()->getPosition().getX()/32 - checkDistanceX;
			PposPlusY = (int)player->getPlayer()->getPosition().getY()/32 + checkDistanceY;
			PposMinusY = (int)player->getPlayer()->getPosition().getY()/32 - checkDistanceY;


			//! Iterates through collision boxes around the player.
			if(PposPlusY < 24)
			{
				for(boxIt = map.getCollisions()->begin()+PposMinus; boxIt != map.getCollisions()->begin()+ PposPlus; ++boxIt)
				{
					for(boxIt2 = boxIt->begin()+PposMinusY; boxIt2 != boxIt->begin()+PposPlusY;++boxIt2)
					{
						//!checks for collision with the player then applys impulse.
						if(collision.CircleToAABB(*player->getPlayer(), *boxIt2, hitFloor,hitSide, hitUnder))
						{
							collision.applyCtoAABBimpulse(*player->getPlayer(), *boxIt2);
							//player->getPlayer()->setVel(Vector2D(player->getPlayer()->getVelocity().getX(),0));
						}


						hitSide=false;
						//! If the player hits a block that is question block then. 
						//!Change the texture of the block to.... And reset bool.
						if(hitUnder && boxIt2->getQuestionBlock())
						{
							boxIt2->setQuestionBlock(false);
							ui.AddtoScore(200);
							ui.AddtoCoins(1);
							aniCoin.Initialise(32,32,boxIt2->getPosition().getX(),boxIt2->getPosition().getY());
							aniCoin.getCoin()->setVel(Vector2D(0.f,-50.f));
							aniCoins.push_back(aniCoin);
							boxIt2->setTextureCoords(27*16,0);
							hitUnder = false;
						}

						//! If the player hits a block that is destroyable then. 
						//!Destroy the block and reset bool.
						if(hitUnder && boxIt2->getDestroyable())
						{

							*boxIt2 = emp;
							hitUnder = false;
						}
						else ;
						hitUnder = false;
					}

				}
			}
			//!Iterates through list of coins checking collisions with the player.
			for(cIt = map.getCoins()->begin(); cIt != map.getCoins()->end();)
			{
				//cIt->Update(REFRESH_RATE);
				if(collision.CircleToAABB(*player->getPlayer(),*cIt->getCoin(),hitFloor,hitSide,hitUnder))
				{
					ui.AddtoCoins(1);
					ui.AddtoScore(200);
					hitUnder = false;
					hitSide = false;
					hitFloor = false;
					cIt = map.getCoins()->erase(cIt);

				}
				else ++cIt;

			}
			//! Iterate Through enemy list. 
			//std::list<Enemy>::iterator eIt;
			for(enemiesIt = map.getEnemies()->begin(); enemiesIt != map.getEnemies()->end();)
			{
				//! Checks if an enemy has collided with the player.
				if(collision.CircleToAABB(*player->getPlayer(),*enemiesIt->getEnemy(),hitEnemy,hitSide,hitUnder))
				{
					collision.applyCtoAABBimpulse(*player->getPlayer(), *enemiesIt->getEnemy());
				}
				//! Returns if enemy has been hit on the top.
				if(hitEnemy)
				{
					ui.AddtoScore(100);
					//! Kills the enemy.
					player->getPlayer()->setVel(Vector2D(player->getPlayer()->getVelocity().getX(), -20));

					//enemiesIt->getEnemy()->setTextureCoords(0.f,10.f*16.f);

					enemyDelete = true;
					//hitEnemy = false;
					hitEnemy = false;
				}


				//! Returns if the enemy has been hit on the side.
				if(hitSide || hitUnder)
				{
					//! Kills / reset the player
					gamestate = GameOver;
					/*view.setCenter(sf::Vector2f(384,newPos));
					player->getPlayer()->setPos(Vector2D(100,700.f));*/
				}
				//! If enemy falls off map then kills enemy.
				if(enemiesIt->getEnemy()->getPosition().getY() > 768.f)
				{
					enemyDelete = true;

				}
				//! If the enemy goes to the left of the view. Then kill the enemy.
				if(enemiesIt->getEnemy()->getPosition().getX() < (view.getCenter().x - view.getSize().x/2)-10)
				{
					enemyDelete = true;
				}

				//!Checks to see if Enemy collision detection is out of range.

				EposPlusX = (int)enemiesIt->getEnemy()->getPosition().getX()/32 + checkDistanceX;
				EposMinusX = (int)enemiesIt->getEnemy()->getPosition().getX()/32 - checkDistanceX;
				EposPlusY = (int)enemiesIt->getEnemy()->getPosition().getY()/32 + checkDistanceY;
				EposMinusY = (int)enemiesIt->getEnemy()->getPosition().getY()/32 - checkDistanceY;





				//! Iterates through collision boxes around the enemies.
				if(EposPlusY <24){
					for(boxIt = map.getCollisions()->begin()+EposMinusX; boxIt != map.getCollisions()->begin()+EposPlusX; ++boxIt)
					{
						for(boxIt2 = boxIt->begin()+EposMinusY; boxIt2 != boxIt->begin()+EposPlusY;++boxIt2)
						{
							if(enemiesIt->getInitialised())//!< If enemies are initialised then check collisions
							{
								if(collision.AABBtoAABB(*enemiesIt->getEnemy(),*boxIt2,normal))
								{
									//enemiesIt->getEnemy().setAcc(Vector2D(0,0));
									collision.applyAABBtoAABBimpulse(*enemiesIt->getEnemy(),*boxIt2);
									if(normal.getX() == 1)
									{
										enemiesIt->getEnemy()->setVel(Vector2D(10,0));
									}
									else if(normal.getX()== -1)
									{
										enemiesIt->getEnemy()->setVel(Vector2D(-10,0));
									}
								}
							}
							//!< If they are not initialised and collide with the detection box then Initialise them.
							if(!enemiesIt->getInitialised() && collision.AABBtoAABB(detectionBox,*enemiesIt->getEnemy(),normal))
							{
								enemiesIt->getEnemy()->setVel(Vector2D(-10.f,0));
								enemiesIt->getEnemy()->setAcc(Vector2D(0,9.81f));
								enemiesIt->setInitialised(true);
							}
						}
					}
				}
				std::list<Enemy>::iterator eIt;
				for(eIt = map.getEnemies()->begin(); eIt != map.getEnemies()->end();++eIt)
				{

					//! Checks Collision between all enemies.
					if(collision.AABBtoAABB(*enemiesIt->getEnemy(),*eIt->getEnemy(),normal) && enemiesIt != eIt)
					{
						collision.applyAABBtoAABBimpulse(*enemiesIt->getEnemy(),*eIt->getEnemy());
						//! Gives them a velocity in x / y if they do collide. 
						if(normal.getX() == 1)
						{
							enemiesIt->getEnemy()->setVel(Vector2D(10,0));
							eIt->getEnemy()->setVel(Vector2D(-10,0));
						}
						else if(normal.getX()== -1)
						{
							enemiesIt->getEnemy()->setVel(Vector2D(-10,0));
							eIt->getEnemy()->setVel(Vector2D(10,0));
						}
					}

				}
				//! Deletes the enemy if boolean is true.
				if(enemyDelete)
				{
					enemiesIt = map.getEnemies()->erase(enemiesIt);
					enemyDelete = false;
				}else ++enemiesIt;




			}
		}	
}

