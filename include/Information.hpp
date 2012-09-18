#ifndef __INFORMATION_HPP__
#define __INFORMATION_HPP__

#include <SFML/Graphics.hpp>

class Information{
	private:
	bool loadError;
	sf::RenderWindow* screen;
	sf::Font font;
	sf::Text scoreLabel;
	sf::Text scoreText;
	unsigned score;
	
	void scoreToString();

	public:
	Information(sf::RenderWindow* window=0);
	~Information(){}
	bool getLoadError();
	void draw();
	void incrementScore();
};

#endif
