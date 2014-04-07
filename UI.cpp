/*!
@UI.cpp
*/
#include "UI.h"

UI::UI()
{

}
void UI::Initialise(sf::View &nView)
{
	view = nView;
	coinBox.getCoin()->setSize(20,20);
	coinBox.getCoin()->setPos(0, 0);
	coinBox.getCoin()->setTextureCoords(30*16,9*16);
	mario.setString("MARIO");//!< Sets string to mario.
	time.setString("TIME");//!< Sets string to time.
	scores = 0;//!< Initial values of score
	coin = 0;//!< Initial value of coins.
	//! Sets the starting Positions.
	coinBox.getCoin()->setPos(view.getCenter().x - 80.f , view.getCenter().y - view.getSize().y /2 +26.f);
	mario.setPosition(view.getCenter().x - view.getSize().x /2 + 50, view.getCenter().y - view.getSize().y /2 +10);//!<Sets the position in the view.
	time.setPosition(view.getCenter().x + view.getSize().x /2 - 150 , view.getCenter().y - view.getSize().y /2 +10);//!<Sets the position in the view.
	ttimer.setPosition(view.getCenter().x + view.getSize().x /2 - 140 , view.getCenter().y - view.getSize().y /2 +30);//!<Sets the position in the view.
	score.setPosition(view.getCenter().x - view.getSize().x /2 + 50 , view.getCenter().y - view.getSize().y /2 +30);//!<Sets the position in the view.
	coins.setPosition(view.getCenter().x - 65.f , view.getCenter().y - view.getSize().y /2 +20.f);//!<Sets the position in the view.
}

void UI::Update(sf::View &nView, float ntime)
{

	//! If the coins reach 100. Change the coins back to 0. Add 1000 to score.
	if(coin == 100)
	{
		AddtoScore(1000);
		coin = 0;
	}

	view = nView;//!< View is = to address of inputted view.
	std::stringstream ss;//creates ss.

	ss.str("");//!<Clears the string.
	ss << std::setw(6) << std::setfill('0') << scores;//!< Sets width to 6. And fills rest with 0
	std::string s = ss.str();//!< Sets the string to the stringstream string.


	ss.str("");//!<Clears the string.
	ss << std::setw(3) << std::setfill('0') << timer;//!< Sets width to 3. And fills rest with 0
	std::string t = ss.str();//!< Sets the string to the stringstream string.
	
	ss.str("");//!<Clears the string.
	ss << 'X' << std::setw(2) << std::setfill('0') << coin;//!< Sets width to 2. And fills rest with 0
	std::string c = ss.str();//!< Sets the string to the stringstream string.

	//! Update Positions
	coinBox.getCoin()->setPos(view.getCenter().x - 80.f , view.getCenter().y - view.getSize().y /2 +26.f);
	mario.setPosition(view.getCenter().x - view.getSize().x /2 + 50, view.getCenter().y - view.getSize().y /2 +10);//!<Sets the position in the view.
	time.setPosition(view.getCenter().x + view.getSize().x /2 - 150 , view.getCenter().y - view.getSize().y /2 +10);//!<Sets the position in the view.
	ttimer.setPosition(view.getCenter().x + view.getSize().x /2 - 140 , view.getCenter().y - view.getSize().y /2 +30);//!<Sets the position in the view.
	score.setPosition(view.getCenter().x - view.getSize().x /2 + 50 , view.getCenter().y - view.getSize().y /2 +30);//!<Sets the position in the view.
	coins.setPosition(view.getCenter().x - 65.f , view.getCenter().y - view.getSize().y /2 +20.f);//!<Sets the position in the view.
	
	//!< CountDown timer.
	if(clock.getElapsedTime().asSeconds() > 1.f)
	{
		if(timer != 0)
		{
			--timer;//!< whenever reaches 1 sec. Countdown.
		}
		clock.restart();
	}
	
	//! Sets string to the local string.
	ttimer.setString(t);
	score.setString(s);
	coins.setString(c);

}
void UI::AddtoScore(unsigned int nScore)
{
	scores += nScore;//!< Adds to score.
}
void UI::AddtoCoins(unsigned int nCoin)
{
	coin += nCoin;//!< Adds to coin
}
void UI::setTime(unsigned int nTime)
{
	timer = nTime;//!< Sets a time.
}
unsigned int UI::getTime()const
{
	return timer;//!< Returns Time.
}
void UI::Reset(sf::View &nView)
{
	timer = 300;//!< Resets to 300.
	coin = 0;//!< Resets to 0.
	scores = 0;//!< Resets to 0.
	view = nView;

	std::stringstream ss;
	ss.str("");
	ss << std::setw(6) << std::setfill('0') << scores;//!< Sets width to 6. And filles rest with 0
	std::string s = ss.str();//!< Sets the string to the stringstream string.
	ss.clear();//!<Clears the stringstream.
	ss.str("");
	ss << 'X' << std::setw(2) << std::setfill('0') << coin;
	std::string c = ss.str();

	score.setString(s);//!<Resets string
	coins.setString(c);//!<Resets string
	ttimer.setString("");

	//!Resets Positions.
	coinBox.getCoin()->setPos(view.getCenter().x - 80.f , view.getCenter().y - view.getSize().y /2 +26.f);
	mario.setPosition(view.getCenter().x - view.getSize().x /2 + 50, view.getCenter().y - view.getSize().y /2 +10);//!<Sets the position in the view.
	time.setPosition(view.getCenter().x + view.getSize().x /2 - 150 , view.getCenter().y - view.getSize().y /2 +10);//!<Sets the position in the view.
	ttimer.setPosition(view.getCenter().x + view.getSize().x /2 - 140 , view.getCenter().y - view.getSize().y /2 +30);//!<Sets the position in the view.
	score.setPosition(view.getCenter().x - view.getSize().x /2 + 50 , view.getCenter().y - view.getSize().y /2 +30);//!<Sets the position in the view.
	coins.setPosition(view.getCenter().x - 65.f , view.getCenter().y - view.getSize().y /2 +20.f);//!<Sets the position in the view.

}
void UI::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	//! Draws everything
	target.draw(ttimer);
	target.draw(time);
	target.draw(score);
	target.draw(mario);
	target.draw(coinBox);
	target.draw(coins);
}
