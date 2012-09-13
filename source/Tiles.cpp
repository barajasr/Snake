#include "Tiles.hpp"
#include <iostream>

Tiles::Tiles(sf::RenderWindow* window):screen(window){
	Tile tile(sf::Vector2f(0, 0));
	std::vector<Tile> tmp(BOARD_X, tile);
	for (unsigned x(0); x < BOARD_X; x++)
		board.push_back(tmp);
	
	board[BOARD_X / 2][BOARD_Y / 2].setTileType(FOOD);

	sf::Vector2f pos;
	for (unsigned x(0); x < BOARD_X; x++)
		for (unsigned y(0); y < BOARD_Y; y++){
			pos.x =  IMAGESIZE * x + x + MARGIN / 2;
			pos.y =  IMAGESIZE * y + y + MARGIN / 2;
			board.at(x).at(y).tile.setPosition(pos);
		}
}
	
void Tiles::draw(){
	for (unsigned x(0); x < BOARD_X; x++)
		for (unsigned y(0); y < BOARD_Y; y++)
			screen->draw(board.at(x).at(y).tile);
}
TileType Tiles::getTileAt(int x, int y){
	return board.at(x).at(y).type;
}

