#pragma once
#include "State.hpp"
#include "GameplaySettings.hpp"
#include <Button.hpp>
class Menu :public State {
public:
	Menu(sf::RenderWindow& window);
	void process_imput()override;
	void update(sf::Time dt)override;
	void draw()override;

private:
	sf::Text title;
	sf::RectangleShape back;
	mpv::Vector<Button> buttons;
};
