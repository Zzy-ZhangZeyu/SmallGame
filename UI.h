#ifndef UI_H
#define UI_H

#include <sstream>
#include <iomanip>
#include "Text.h"
#include "Box.h"
#include "LoadTexture.h"
#include "Coin.h"

/*! \brief Hold the User Interface time, score and coins.*/
class UI: public sf::Drawable
{
private:
	Text time,score,mario,coins, ttimer;
	Text menu;
	sf::Clock clock;
	sf::View view;
	unsigned int scores;//!< Holds the score.
	unsigned int timer;//!< Holds the time.
	unsigned int coin;//!< Holds amount of Coins.
	//Box box;
	Coin coinBox;
	
public:
	UI();
	~UI(){};
	void Initialise(sf::View &nView);//!< Sets default params for the UI.
	void Update(sf::View &nView, float ntime);//!< Updates the scores time and coins and view.
	void AddtoScore(unsigned int nScore);//!< Adds to score.
	void AddtoCoins(unsigned int nCoin);//!< Adds to coins
	void setTime(unsigned int nTime);//!< sets the timer.
	void Reset(sf::View &nView);//!< Resets view and all values and strings.
	unsigned int getTime()const;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;//!< Draws
};
#endif