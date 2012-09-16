#include "Tiles.hpp"
#include "Snake.hpp"
#include <cstdlib>
#include <ctime>

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
	food.x = food.y = BOARD_X / 2;
}

sf::Vector2f Tiles::getFood(){
	return board.at(food.x).at(food.y).tile.getPosition();
}

TileType Tiles::getTileAt(int x, int y){
	return board.at(x).at(y).type;
}

void Tiles::draw(){
	for (unsigned x(0); x < BOARD_X; x++)
		for (unsigned y(0); y < BOARD_Y; y++)
			screen->draw(board.at(x).at(y).tile);
}

void Tiles::levelUp(Snake* snake){

	srand(time(0));
	sf::Vector2f newFood(0, 0);

	for (bool valid=false; !valid;){
		newFood = sf::Vector2f(rand() % BOARD_X, rand() % BOARD_Y);
		valid = !(snake->collidesWith(board.at(newFood.x).at(newFood.y).tile.getPosition()));
	}
	board[food.x][food.y].setTileType(EMPTY);
	board[newFood.x][newFood.y].setTileType(FOOD);
	food.x = newFood.x;
	food.y = newFood.y;
}

