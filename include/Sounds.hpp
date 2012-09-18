#ifndef __SOUNDS_HPP__
#define __SOUNDS_HPP__

#include <SFML/Audio.hpp>

class Sounds{
	private:
	bool loadError;
	sf::Sound ateFood;
	sf::Sound hitHazard;
	sf::SoundBuffer food;
	sf::SoundBuffer hazard;

	bool wait();

	public:
	Sounds();
	~Sounds();
	bool getLoadError();
	void playAteFood();
	void playHitHazard();
};

#endif
