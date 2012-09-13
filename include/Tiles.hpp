#ifndef __TILES_HPP__
#define __TILES_HPP__

#include "Definitions.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Tiles{
	private:
	sf::RenderWindow* screen;
	std::vector<std::vector<Tile> >  board;

	public:
	Tiles(sf::RenderWindow* window=0);
	~Tiles(){}
	void draw();
	TileType getTileAt(int x, int y);
};

#endif
