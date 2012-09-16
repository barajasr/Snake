#include "Snake.hpp"
#include "Tiles.hpp"
#include "Definitions.hpp"

Snake::Snake(sf::RenderWindow* window, unsigned size)
		:firstMove(true), direction(RIGHT), frameSpeed(8), speedTrigger(3), screen(window){
	frameTrigger = frameSpeed;
	sf::RectangleShape tmp;
	tmp.setSize(sf::Vector2f(IMAGESIZE, IMAGESIZE));
	tmp.setFillColor(sf::Color(0, 100, 0));
	sf::Vector2f pos(MARGIN / 2.0f, MARGIN / 2.0f);
	tmp.setPosition(pos);

	for (unsigned i(0); i < size; i++)
		body.push_back(tmp);
}

Snake::~Snake(){}

bool Snake::ateFood(sf::Vector2f position){
	sf::Vector2f head = body.at(0).getPosition();
	return ((head.x == position.x) && (head.y == position.y));
}

bool Snake::collidesWith(sf::Vector2f position){
	sf::Vector2f bodyPosition(0, 0);
	for (unsigned index(0); index <	body.size(); index++){
		bodyPosition = body.at(index).getPosition();
		if ((bodyPosition.x == position.x) && (bodyPosition.y == position.y))
			return true;
	}
	return false;
}

bool Snake::edgeCollision(){
	sf::Vector2f pos = body.at(0).getPosition();
	if (pos.x < MARGIN/2 || pos.x > (WINDOW_X - MARGIN/2)
			|| pos.y < MARGIN/2 || pos.y > (WINDOW_Y - MARGIN/2 - SCORE_MARGIN))
		return true;
	return false;
}

bool Snake::selfCollision(){
	sf::Vector2f head = body.at(0).getPosition();
	sf::Vector2f current = body.at(1).getPosition();
	if ((head.x == current.x) && (head.y == current.y))
			return false;

	for (unsigned index(1); index < body.size(); index++){
		current = body.at(index).getPosition();
		if ((head.x == current.x) && (head.y == current.y))
			return true;
	}
	return false;
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
	}
	choice = direction;
	return choice;
}

void Snake::addTailPiece(){
	body.push_back(body.at(body.size() - 1));
}

void Snake::draw(){
	for (unsigned x(0); x < body.size(); x++)
		screen->draw(body.at(x));
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

// position is location of Food tile,
// used for determining if object was ate.
void Snake::update(Tiles* tiles, sf::Vector2f position){
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

		// Check if ate food
		if (ateFood(position)){
			addTailPiece();
			tiles->levelUp(this);

			// Check if snake speeds up
			speedTrigger--;
			if (speedTrigger <= 0){
				if(frameSpeed > 0)
					frameSpeed--;
				speedTrigger = 3;
			}
		}
		frameTrigger = frameSpeed;
	}
	if (frameSpeed > 0)
		frameTrigger--;
}
