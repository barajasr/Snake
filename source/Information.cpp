#include "Information.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

Information::Information(sf::RenderWindow* window)
		:loadError(false), screen(window), score(0){
	if (!font.loadFromFile("Data/arial.ttf"))
		loadError = true;

	if (!loadError){
		scoreLabel.setFont(font);
		scoreLabel.setString("Score:");
		scoreLabel.setCharacterSize(20);
		scoreLabel.setColor(sf::Color::White);
		scoreLabel.setPosition(sf::Vector2f(MARGIN, WINDOW_Y - SCORE_MARGIN));

		scoreText.setFont(font);
		scoreText.setString("0");
		scoreText.setCharacterSize(20);
		scoreText.setColor(sf::Color::White);
		scoreText.setPosition(sf::Vector2f(WINDOW_X / 7, WINDOW_Y - SCORE_MARGIN));

	}else{
		std::cerr << "Failure to load Data/FreeMono.tff" << std::endl;
	}
}

bool Information::getLoadError(){
	return loadError;
}

void Information::draw(){
	screen->draw(scoreLabel);
	screen->draw(scoreText);
}

void Information::incrementScore(){
	score++;
	scoreToString();
}

void Information::scoreToString(){
	std::stringstream ss;
	ss << score;
	scoreText.setString(ss.str());
}
