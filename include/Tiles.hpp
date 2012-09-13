#ifndef __TILES_HPP__
#define __TILES_HPP__

#include "Definitions.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Tiles{
	private:
	sf::RectangleShape rect;
	sf::RenderWindow* screen;
	std::vector<std::vector<Tile> >  board;

	sf::Color newColor(Tile tile);
	public:
	Tiles(sf::RenderWindow* window=0);
	~Tiles(){}
	void draw();
	Tile getTileAt(int x, int y);
};

#endif
