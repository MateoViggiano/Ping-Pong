#pragma once
#include <SFML/Graphics.hpp>
#include <viggiano.hpp>
class State {
protected:
	sf::RenderWindow& window;
public:
	State(sf::RenderWindow& window):window(window) {}
	virtual ~State() {}
	virtual void process_imput() = 0;
	virtual void update(sf::Time dt) = 0;
	virtual void draw() = 0;
	virtual void enter() {}
	virtual void exit() {}

};
