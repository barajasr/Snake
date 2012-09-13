#include "Snake.hpp"
#include "Definitions.hpp"
#include <iostream>

Snake::Snake(sf::RenderWindow* window):
		 direction(RIGHT), screen(window), frameSpeed(8){
	frameTrigger = frameSpeed;
	sf::RectangleShape tmp;
	tmp.setSize(sf::Vector2f(IMAGESIZE, IMAGESIZE));
	tmp.setFillColor(sf::Color(0, 100, 0));
	sf::Vector2f pos(MARGIN / 2.0f, MARGIN / 2.0f);
	tmp.setPosition(pos);
	for(int i(0); i < 4; i++)
		body.push_back(tmp);
	
	
}

Snake::~Snake(){}

void Snake::draw(){
	for (unsigned x(0); x < body.size(); x++)
		screen->draw(body.at(x));
}

Direction Snake::newDirection(){
	Direction choice= directionQueue.front();
	while (!directionQueue.empty()){
		choice = directionQueue.front();
		directionQueue.pop();

		switch(direction){
		case UP:
		case DOWN:
			if (choice != DOWN && choice != UP)
				return choice;
			break;
		case LEFT:
		case RIGHT:
			if (choice != LEFT && choice != RIGHT)
				return choice;
			break;
		}
		choice = direction;
	}
	return choice;
}

void Snake::process(const sf::Event event){
	if (event.type == sf::Event::KeyPressed){
		if (event.key.code == sf::Keyboard::Up)
			directionQueue.push(UP);
		else if (event.key.code == sf::Keyboard::Down)
			directionQueue.push(DOWN);
		else if (event.key.code == sf::Keyboard::Left)
			directionQueue.push(LEFT);
		else if (event.key.code == sf::Keyboard::Right)
			directionQueue.push(RIGHT);
	}	
}

bool Snake::selfCollision(){
		sf::Vector2f head = body.at(0).getPosition();
		sf::Vector2f current = head;
	for (unsigned i(0); i < body.size(); i++)
		current	= body.at(i).getPosition();
		if (head.x == current.x && head.y == current.y)
			return true;
	return false;

}
void Snake::update(){
	if (frameTrigger <= 0){
		if (!directionQueue.empty())
			direction = newDirection();
	
		for (unsigned i(body.size()-1); i > 0; i--)
			body[i].setPosition(body.at(i-1).getPosition());
	
		sf::Vector2f pos(body.at(0).getPosition());
		switch(direction){
		case UP:
			body[0].setPosition(pos.x, pos.y - IMAGESIZE - 1);
			break;
		case DOWN:
			body[0].setPosition(pos.x, pos.y + IMAGESIZE + 1);
			break;
		case LEFT:
			body[0].setPosition(pos.x - IMAGESIZE - 1, pos.y);
			break;
		case RIGHT:
			body[0].setPosition(pos.x + IMAGESIZE + 1, pos.y);
			break;
		}
		frameTrigger = frameSpeed;
	}
	if (frameSpeed > 0)
		frameTrigger--;
}
