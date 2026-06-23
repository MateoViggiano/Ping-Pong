#pragma once
#include "State.hpp"
#include "GameplaySettings.hpp"
#include <Button.hpp>
#include <TextBox.hpp>
class SinglePlayerConfigMenu :public State {
private:
	sf::Text title;
	sf::RectangleShape back;
	mpv::Vector<Button> buttons;
	mpv::Vector<TextBox> text_boxes;
	mpv::Vector<sf::Text> texts;
	PlayerType lplayer = BOT, rplayer = MOUSEPLAYER;
	GameplaySettings read_settings()const;
public:
	SinglePlayerConfigMenu(sf::RenderWindow& window);
	void process_imput()override;
	void update(sf::Time dt)override;
	void draw()override;

};
