#ifndef __TILES_HPP__
#define __TILES_HPP__

#include "Definitions.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Snake;

class Tiles{
	private:
	const int addHazardRate;
	int hazardTrigger;
	sf::RenderWindow* screen;
	std::vector<std::vector<Tile>>  board;
	std::vector<sf::Vector2f> hazards;
	sf::Vector2f food;

	bool conflictsWithHazards(sf::Vector2f position);
	void addHazard(Snake* snake);
	void newFoodLocation(Snake* snake);
	
	public:
	Tiles(sf::RenderWindow* window=0);
	~Tiles(){}
	sf::Vector2f getFood();
	std::vector<sf::Vector2f> getHazards();
	void draw();
	void levelUp(Snake* snake);
};

#endif
