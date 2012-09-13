#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include "Definitions.hpp"

class Snake{
	private:
	Direction direction;
	int frameTrigger;
	std::queue<Direction> directionQueue;
	sf::RenderWindow* screen;
	const unsigned frameSpeed;
	std::vector<sf::RectangleShape> body;

	Direction newDirection();
	public:
	Snake(sf::RenderWindow* window=0);
	~Snake();
	void draw();
	void print();
	void process(const sf::Event event);
	bool selfCollision();
	void update();
};

#endif
