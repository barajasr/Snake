#include "Game.hpp"
#include "Snake.hpp"
#include "Sounds.hpp"
#include "Tiles.hpp"
#include "Information.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

Game::Game():errors(false){
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y),
								"Snake", sf::Style::Close);

	if (window){
		window->setFramerateLimit(60);
		window->setKeyRepeatEnabled(false);
		
		icon = new sf::Image();
		if (!icon->loadFromFile("Data/icon.png")){
			std::cerr << "ERROR: Failed to load icon; Data/icon.png\n";
			errors = true;
			return;
		}
		window->setIcon(32,32,icon->getPixelsPtr());

		tiles = new Tiles(window);
		snake = new Snake(window);
		info = new Information(window);
		sounds = new Sounds();		
		if (!tiles && !snake && !info && !sounds){
			std::cerr << "ERROR: Insufficient memory to allocate game resources\n";
			errors = true;
			return;
		}

		if (sounds->getLoadError() || info->getLoadError()){
			errors = true;
			return;
		}
	}else{
		errors = true;
		std::cerr << "ERROR: Was not able to initialize the window.\n";
	}	
	
}

Game::~Game(){
	if(icon)
		delete icon;
	if (info)
		delete info;
	if (window)
		delete window;
	if (snake)
		delete snake;
	if (sounds)
		delete sounds;
	if (tiles)
		delete tiles;
}

bool Game::getError(){
	return errors;
}

void Game::reset(){

}

void Game::run(){
	sf::Event event;
	sf::Color background(sf::Color::Black);
	bool gameover(false);
	
	while (window->isOpen() && !gameover){
		while (window->pollEvent(event)){
			if (event.type == sf::Event::KeyPressed)
				snake->process(event);
			else if (event.type == sf::Event::KeyReleased)
				snake->process(event);
			else if (event.type == sf::Event::Closed)
				window->close();
		}

		snake->update(tiles, info, sounds);
		gameover = snake->edgeCollision() || snake->selfCollision() || snake->collidesWith(tiles->getHazards());
		if (gameover)
			sounds->playHitHazard();

		window->clear(background);
		tiles->draw();
		snake->draw();
		info->draw();
		window->display();	
	}

	window->close();
}
