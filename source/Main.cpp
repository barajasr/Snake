#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Tiles.hpp"

int main(){
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), 
							"Snake", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Image icon;
	if (!icon.loadFromFile("Data/icon.png"))
		return -1;
	window.setIcon(32,32,icon.getPixelsPtr());

	Tiles tiles(&window);
	Snake snake(&window);
	sf::Event event;
	sf::Color background(sf::Color::Black);
	bool end = false;

	while (window.isOpen() && (end == false)){
		while (window.pollEvent(event)){
			if (event.type == sf::Event::KeyPressed){
				snake.process(event);
			}else if (event.type == sf::Event::KeyReleased){
				snake.process(event);
			}else if (event.type == sf::Event::Closed)
				window.close();
		}

		snake.update(&tiles);
		end = snake.edgeCollision() || snake.selfCollision() || snake.collidesWith(tiles.getHazards());

		window.clear(background);
		tiles.draw();
		snake.draw();
		window.display();
	}

	window.close();
	return 0;
}
