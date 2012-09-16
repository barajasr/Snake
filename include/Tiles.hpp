#ifndef __TILES_HPP__
#define __TILES_HPP__

#include "Definitions.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Snake;

class Tiles{
	private:
	sf::RenderWindow* screen;
	std::vector<std::vector<Tile>>  board;
	sf::Vector2f food;

	public:
	Tiles(sf::RenderWindow* window=0);
	~Tiles(){}
	sf::Vector2f getFood();
	TileType getTileAt(int x, int y);
	void draw();
	void levelUp(Snake* snake);
};

#endif
