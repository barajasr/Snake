#ifndef __GAME_HPP__
#define __GAME_HPP__

class Information;
class Snake;
class Sounds;
class Tiles;
namespace sf{
	class RenderWindow;
	class Image;
}

class Game{
	private:
	bool errors;
	sf::Image* icon;
	Information* info;
	sf::RenderWindow* window;
	Snake* snake;
	Sounds* sounds;
	Tiles* tiles;
	
	void reset();
	
	public:
	Game();
	~Game();
	bool getError();
	void run();
};

#endif
