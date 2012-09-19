#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include "Definitions.hpp"

class Tiles;
class Information;
class Sounds;

class Snake{
	private:
	bool firstMove;
	bool stop;
	Direction direction;
	int frameSpeed;
	int frameTrigger;
	int speedTrigger;
	std::queue<Direction> directionQueue;
	sf::RenderWindow* screen;
	std::vector<sf::RectangleShape> body;
	unsigned initialSize;

	Direction newDirection();
	public:
	Snake(sf::RenderWindow* window=0, unsigned size=5);
	~Snake();
	bool ateFood(sf::Vector2f position);
	bool collidesWith(sf::Vector2f position);
	bool collidesWith(std::vector<sf::Vector2f> list);
	bool edgeCollision();
	bool selfCollision();
	void addTailPiece();
	void draw();
	void print();
	void process(const sf::Event event);
	void reset();
	void update(Tiles* tiles, Information* info, Sounds* sounds);
};

#endif
