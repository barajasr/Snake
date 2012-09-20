#include "Definitions.hpp"
#include "Information.hpp"
#include "Snake.hpp"
#include  "Sounds.hpp"
#include "Tiles.hpp"

Snake::Snake(sf::RenderWindow* window, unsigned size)
		:firstMove(true), stop(false), direction(RIGHT), 
		frameSpeed(8),speedTrigger(3), screen(window), initialSize(size){
	frameTrigger = frameSpeed;
	sf::RectangleShape tmp;
	tmp.setSize(sf::Vector2f(IMAGESIZE, IMAGESIZE));
	tmp.setFillColor(sf::Color(0, 100, 0));
	sf::Vector2f pos(MARGIN / 2.0f, MARGIN / 2.0f);
	tmp.setPosition(pos);

	for (unsigned i(0); i < initialSize; i++)
		body.push_back(tmp);
}

Snake::~Snake(){}

bool Snake::ateFood(const sf::Vector2f& position) const{
	sf::Vector2f head = body.at(0).getPosition();
	return ((head.x == position.x) && (head.y == position.y));
}

bool Snake::collidesWith(const sf::Vector2f& position) const{
	sf::Vector2f bodyPosition(0, 0);
	for (unsigned index(0); index <	body.size(); index++){
		bodyPosition = body.at(index).getPosition();
		if ((bodyPosition.x == position.x) && (bodyPosition.y == position.y))
			return true;
	}
	return false;
}

bool Snake::collidesWith(const std::vector<sf::Vector2f>& list) const{
	if (!list.empty()){
		for (unsigned index(0); index <	list.size(); index++)
			if (collidesWith(list.at(index)))
				return true;
	}
	return false;
}

bool Snake::edgeCollision() const{
	sf::Vector2f pos = body.at(0).getPosition();
	if (pos.x < MARGIN/2 || pos.x > (WINDOW_X - MARGIN/2)
			|| pos.y < MARGIN/2 || pos.y > (WINDOW_Y - MARGIN/2 - SCORE_MARGIN))
		return true;
	return false;
}

bool Snake::selfCollision() const{
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

void Snake::draw() const{
	for (unsigned x(0); x < body.size(); x++)
		screen->draw(body.at(x));
}

void Snake::process(const sf::Event& event){
	if (event.type == sf::Event::KeyPressed){
		if (event.key.code == sf::Keyboard::Up)
			directionQueue.push(UP);
		else if (event.key.code == sf::Keyboard::Down)
			directionQueue.push(DOWN);
		else if (event.key.code == sf::Keyboard::Left)
			directionQueue.push(LEFT);
		else if (event.key.code == sf::Keyboard::Right)
			directionQueue.push(RIGHT);
		else if (event.key.code == sf::Keyboard::Space)
			stop = !stop;
	}	
}

void Snake::reset(){
	firstMove = true;
	stop = false;
	direction = RIGHT;
	frameSpeed = 8;
	frameTrigger = frameSpeed;

	while (body.size() > initialSize + 1){
		body.pop_back();
	}

	sf::Vector2f position(MARGIN / 2, MARGIN / 2);
	for (unsigned index(0); index < initialSize; index++)
		body.at(index).setPosition(position);
}

void Snake::update(Tiles* tiles, Information* info, Sounds* sounds){
	if (stop){
		if (!info->isPaused())
			info->pauseToggle();		
		return;
	}else {
		if (info->isPaused())
			info->pauseToggle();
	}

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

		// Check if ate food and applicable side effects
		if (ateFood(tiles->getFood())){
			addTailPiece();
			tiles->levelUp(this);

			// Check if snake speeds up
			speedTrigger--;
			if (speedTrigger <= 0){
				if(frameSpeed > 0)
					frameSpeed--;
				speedTrigger = 3;
			}

			info->incrementScore();
			sounds->playAteFood();
		}

		frameTrigger = frameSpeed;
	}
	if (frameSpeed > 0)
		frameTrigger--;
}
