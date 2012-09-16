#ifndef __DEFINITIONS_HPP__
#define __DEFINITIONS_HPP__

#include <SFML/Graphics.hpp>

enum Direction{UP, DOWN, LEFT, RIGHT};
enum TileType{EMPTY, FOOD, HAZARD};

// Constants for 2D gameboard, max indices
const unsigned BOARD_X = 61;
const unsigned BOARD_Y = 61;

const unsigned IMAGESIZE = 8;

// Total margin between gameboard and window, in pixels
// MARGIN/2 to be exact for left, top, right
const unsigned MARGIN = 10;
const unsigned SCORE_MARGIN = 30;	// specific to bottom

const unsigned WINDOW_X = BOARD_X * IMAGESIZE + BOARD_X + MARGIN - 1;
const unsigned WINDOW_Y = BOARD_Y * IMAGESIZE + BOARD_Y + MARGIN + SCORE_MARGIN - 1;

struct Tile{
	TileType type;
	sf::RectangleShape tile;
	Tile(sf::Vector2f pos, unsigned imageSize=IMAGESIZE, TileType tType=EMPTY){
		sf::Color color = getNewTileFill(tType);
		tile.setSize(sf::Vector2f(imageSize,imageSize));
		tile.setPosition(pos);
		tile.setFillColor(color);
	}
	sf::Color getNewTileFill(TileType tType){
		sf::Color color;
		switch(tType){
		default:
		case EMPTY:
			color = sf::Color(211, 211, 211);
			break;
		case FOOD:
			color = sf::Color::Red;
			break;
		case HAZARD:
			color = sf::Color::Magenta;
			break;
		}
		return color;
		
	}
	void setTileType(TileType tType){
		type = tType;
		tile.setFillColor(getNewTileFill(tType));
	}
};
#endif
