#ifndef __INFORMATION_HPP__
#define __INFORMATION_HPP__

#include <SFML/Graphics.hpp>
#include <vector>

class Information{
	private:
	bool loadError;
	bool paused;
	sf::RenderWindow* screen;
	sf::Font font;
	sf::Text pausedLabel;
	sf::Text scoreLabel;
	sf::Text scoreText;
	std::vector<sf::Text> controlsList;
	unsigned score;
	
	void scoreToString();

	public:
	Information(sf::RenderWindow* window=0);
	~Information(){}
	bool getLoadError();
	bool isPaused();
	void draw();
	void incrementScore();
	void pauseToggle();
};

#endif
