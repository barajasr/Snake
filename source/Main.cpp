#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Sounds.hpp"
#include "Tiles.hpp"
#include "Information.hpp"

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
	Information information(&window);
	if (information.getLoadError())
		return 1;
	Sounds sounds;
	if (sounds.getLoadError())
		return 1;


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

		snake.update(&tiles, &information, &sounds);
		end = snake.edgeCollision() || snake.selfCollision() || snake.collidesWith(tiles.getHazards());
		if (end)
			sounds.playHitHazard();

		window.clear(background);
		tiles.draw();
		snake.draw();
		information.draw();
		window.display();
	}

	window.close();
	return 0;
}
