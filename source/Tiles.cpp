#include "Tiles.hpp"
#include "Snake.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Tiles::Tiles(sf::RenderWindow* window)
		:addHazardRate(2), hazardTrigger(addHazardRate), screen(window){
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

	board[BOARD_X / 2][BOARD_Y /3].setTileType(HAZARD);
	hazards.push_back(sf::Vector2f(BOARD_X / 2, BOARD_Y / 3));
}

bool Tiles::conflictsWithHazards(sf::Vector2f position){
	sf::Vector2f current(0, 0);
	for (unsigned index(0); index < hazards.size(); index++){
		current = hazards.at(index);
		if ((position.x == current.x) && (position.y == current.y))
			return true;
	}
	return false;
}

sf::Vector2f Tiles::getFood(){
	return board.at(food.x).at(food.y).tile.getPosition();
}

std::vector<sf::Vector2f> Tiles::getHazards(){
	std::vector<sf::Vector2f> list;
	sf::Vector2f position;
	for (unsigned index(0); index < hazards.size(); index++){
		position = hazards.at(index);
		list.push_back(board.at(position.x).at(position.y).tile.getPosition());
	}

	return list;
}

void Tiles::addHazard(Snake* snake){
	srand(time(0));
	sf::Vector2f newTile(0, 0);
	sf::Vector2f current = newTile;

	for (bool valid=false; !valid;){
		newTile = sf::Vector2f(rand() % BOARD_X, rand() % BOARD_Y);
		current = board.at(newTile.x).at(newTile.y).tile.getPosition();
		valid = !snake->collidesWith(current) && !conflictsWithHazards(newTile)
				&& newTile != food;
	}
	board[newTile.x][newTile.y].setTileType(HAZARD);
	hazards.push_back(newTile);
}

void Tiles::draw(){
	for (unsigned x(0); x < BOARD_X; x++)
		for (unsigned y(0); y < BOARD_Y; y++)
			screen->draw(board.at(x).at(y).tile);
}

void Tiles::levelUp(Snake* snake){
	newFoodLocation(snake);

	if (--hazardTrigger <= 0){
		addHazard(snake);
		hazardTrigger = addHazardRate;
	}
}

void Tiles::newFoodLocation(Snake* snake){
	srand(time(0));
	sf::Vector2f newTile(0, 0);
	sf::Vector2f current = newTile;

	for (bool valid=false; !valid;){
		newTile = sf::Vector2f(rand() % BOARD_X, rand() % BOARD_Y);
		current = board.at(newTile.x).at(newTile.y).tile.getPosition();
		valid = !snake->collidesWith(current) && !conflictsWithHazards(newTile);
	}

	board[food.x][food.y].setTileType(EMPTY);
	board[newTile.x][newTile.y].setTileType(FOOD);
	food.x = newTile.x;
	food.y = newTile.y;
}
