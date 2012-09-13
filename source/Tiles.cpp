#include "Tiles.hpp"
#include <iostream>

Tiles::Tiles(sf::RenderWindow* window):screen(window){
	std::vector<Tile> tmp(BOARD_X, EMPTY);
	for (unsigned x(0); x < BOARD_X; x++)
		board.push_back(tmp);
	
	board[BOARD_X / 2][BOARD_Y / 2] = FOOD;

	rect.setSize(sf::Vector2f(IMAGESIZE, IMAGESIZE));
	rect.setFillColor(sf::Color::White);	
}
	
sf::Color Tiles::newColor(Tile tile){
	sf::Color choice(0, 0, 0);
	switch(tile){
	case EMPTY:
		choice = sf::Color(211, 211, 211);
		break;
	case FOOD:
		choice = sf::Color::Red;
		break;
	case HAZARD:
		choice = sf::Color::Magenta;
		break;
	}
	return choice;
}

void Tiles::draw(){
	sf::Vector2f pos(0, 0);
	Tile previous(EMPTY);
	Tile current(EMPTY);

	for (unsigned x(0); x < BOARD_X; x++)
		for (unsigned y(0); y < BOARD_Y; y++){
			current = getTileAt(x, y);
			pos.x = IMAGESIZE * x + x + MARGIN / 2;
			pos.y = IMAGESIZE * y + y + MARGIN / 2;
			if (y != 0 && previous != current)
				rect.setFillColor(newColor(board.at(x).at(y)));
			rect.setPosition(pos);
			screen->draw(rect);
			previous = current;
		}	
}
Tile Tiles::getTileAt(int x, int y){
	return board.at(x).at(y);
}

