#pragma once
#include "State.hpp"
#include <Button.hpp>
class Pause : public State {
public:
	Pause(sf::RenderWindow& window);
	void process_imput() override;
	void update(sf::Time dt) override;
	void draw() override;

private:
	sf::Text title;
	sf::RectangleShape back;
	mpv::Vector<Button> buttons;
};
