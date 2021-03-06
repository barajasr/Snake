#include "Information.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

Information::Information(sf::RenderWindow* window)
		:loadError(false), paused(false), screen(window), score(0){
	if (!font.loadFromFile("Data/arial.ttf"))
		loadError = true;

	if (!loadError){
		unsigned yPosition = WINDOW_Y - SCORE_MARGIN;

		scoreLabel.setFont(font);
		scoreLabel.setString("Score:");
		scoreLabel.setCharacterSize(20);
		scoreLabel.setColor(sf::Color::White);
		scoreLabel.setPosition(sf::Vector2f(MARGIN, yPosition));

		scoreText = scoreLabel;
		scoreText.setString("0");
		scoreText.setPosition(sf::Vector2f(WINDOW_X / 7, yPosition));

		unsigned xPosition = 429;
		sf::Text tmp = scoreLabel;
		tmp.setCharacterSize(11);
		tmp.setPosition(sf::Vector2f(xPosition, yPosition));
		tmp.setString("Arrow Keys: Direction");
		controlsList.push_back(tmp);

		tmp.setString("Space bar: Pause");
		tmp.setPosition(sf::Vector2f(xPosition, yPosition + 11));
		controlsList.push_back(tmp);

		pausedLabel = scoreLabel;
		pausedLabel.setString("PAUSED");
		pausedLabel.setPosition(242, yPosition); 
	}else{
		std::cerr << "Failure to load Data/arial.tff" << std::endl;
	}
}

Information::~Information(){}

bool Information::getLoadError() const{
	return loadError;
}

bool Information::isPaused() const{
	return paused;
}

void Information::draw() const{
	screen->draw(scoreLabel);
	screen->draw(scoreText);
	for (unsigned index(0); index < controlsList.size(); index++)
		screen->draw(controlsList.at(index));
	if (paused)
		screen->draw(pausedLabel);
}

void Information::gameOverDisplay() const{
	sf::Text text = pausedLabel;
	text.setCharacterSize(14);
	text.setString("GAME OVER... Press <R> to restart");
	text.setPosition(sf::Vector2f(145, WINDOW_Y - SCORE_MARGIN + 2)); 
	screen->draw(text);
}

void Information::incrementScore(){
	score++;
	scoreToString();
}

void Information::pauseToggle(){
	paused = !paused;
}

void Information::reset(){
		scoreText.setString("0");
}

void Information::scoreToString(){
	std::stringstream ss;
	ss << score;
	scoreText.setString(ss.str());
}
