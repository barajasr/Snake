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
	bool ateFood(const sf::Vector2f& position) const;
	bool collidesWith(const sf::Vector2f& position) const;
	bool collidesWith(const std::vector<sf::Vector2f>& list) const;
	bool edgeCollision() const;
	bool selfCollision() const;
	void addTailPiece();
	void draw() const;
	void process(const sf::Event& event);
	void reset();
	void update(Tiles* tiles, Information* info, Sounds* sounds);
};

#endif
