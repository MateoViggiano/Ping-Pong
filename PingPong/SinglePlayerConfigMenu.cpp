#pragma once
#include "SinglePlayerConfigMenu.hpp"
#include "AssetManager.hpp"
#include "GameplaySettings.hpp"
#include "Gameplay.hpp"
#include "functions.hpp"
extern mpv::StateMachine<State> state_manager;
extern AssetManager asset_manager;
//constexpr GameplaySettings DEFAULT_SETTINGS(sf::seconds(10.f), 1, 100, 10, 2000, 500, 50, BOT, MOUSEPLAYER);
constexpr GameplaySettings DEFAULT_SETTINGS(sf::seconds(0.f), 100, 100, 10, 2000, 500, 50, WALL, WALL);
using mpv::parseFloat;
using mpv::parseUint;
GameplaySettings SinglePlayerConfigMenu::read_settings()const{
	return GameplaySettings(sf::seconds((float)parseFloat(text_boxes[0].get_string().getData())), parseUint(text_boxes[1].get_string().getData()), (float)parseFloat(text_boxes[2].get_string().getData()), (float)parseFloat(text_boxes[3].get_string().getData()), (float)parseFloat(text_boxes[4].get_string().getData()), (float)parseFloat(text_boxes[5].get_string().getData()), (float)parseFloat(text_boxes[6].get_string().getData()), lplayer, rplayer);
}

SinglePlayerConfigMenu::SinglePlayerConfigMenu(sf::RenderWindow& window) : State(window), title(asset_manager.get_font(TITLE), "Game Settings"),lplayer(DEFAULT_SETTINGS.lplayer), rplayer(DEFAULT_SETTINGS.rplayer) {
	sf::Vector2f winSize = window.getView().getSize();
	back.setFillColor(sf::Color(0, 0, 150));
	back.setSize({ 600.f,winSize.y * 0.8f });
	back.setPosition({ winSize.x / 2.f - back.getSize().x / 2,winSize.y * 0.1f });
	title.setCharacterSize(40);
	title.setFillColor(sf::Color::Black);
	title.setPosition({ back.getPosition().x + back.getSize().x * 0.1f, winSize.y * 0.15f});


	buttons.emplace_back(sf::Vector2f(winSize.x / 2.f - 150.f, back.getPosition().y + back.getSize().y * 0.85f), sf::Vector2f(300.f, 70.f), asset_manager.get_font(BUTTON), "Play", [this]() {
		state_manager.push(new Gameplay(this->window, this->read_settings()));
	});
	buttons.emplace_back(back.getPosition() + back.getSize() * 0.01f, sf::Vector2f(80.f, 30.f), asset_manager.get_font(BUTTON), "<", [&window]() {
		state_manager.pop();
	});

	float label_x = back.getPosition().x + back.getSize().x * 0.08f;
	float input_x = back.getPosition().x + back.getSize().x * 0.55f;
	float y = winSize.y * 0.22f;
	float spacing = 60.f;
	const sf::Font& tbFont = asset_manager.get_font(TEXTBOX);

	texts.emplace_back(tbFont, sf::String("New ball time (s):"), 18u);
	texts.back().setFillColor(sf::Color::Black);
	texts.back().setPosition({ label_x, y });
	text_boxes.emplace_back(sf::Vector2f(input_x, y), sf::Vector2f(150.f, 40.f), tbFont, sf::String(std::to_string((int)DEFAULT_SETTINGS.new_ball_time.asSeconds())), 18u, sf::Color::Black, sf::Color(100,100,100), sf::Color::White, sf::Color::White);
	y += spacing;

	texts.emplace_back(tbFont, sf::String("Ball max:"), 18u);
	texts.back().setFillColor(sf::Color::Black);
	texts.back().setPosition({ label_x, y });
	text_boxes.emplace_back(sf::Vector2f(input_x, y), sf::Vector2f(150.f, 40.f), tbFont, sf::String(std::to_string((int)DEFAULT_SETTINGS.ball_max)), 18u, sf::Color::Black, sf::Color(100,100,100), sf::Color::White, sf::Color::White);
	y += spacing;

	texts.emplace_back(tbFont, sf::String("Player height:"), 18u);
	texts.back().setFillColor(sf::Color::Black);
	texts.back().setPosition({ label_x, y });
	text_boxes.emplace_back(sf::Vector2f(input_x, y), sf::Vector2f(150.f, 40.f), tbFont, sf::String(std::to_string((int)DEFAULT_SETTINGS.player_heigth)), 18u, sf::Color::Black, sf::Color(100,100,100), sf::Color::White, sf::Color::White);
	y += spacing;

	texts.emplace_back(tbFont, sf::String("Ball size:"), 18u);
	texts.back().setFillColor(sf::Color::Black);
	texts.back().setPosition({ label_x, y });
	text_boxes.emplace_back(sf::Vector2f(input_x, y), sf::Vector2f(150.f, 40.f), tbFont, sf::String(std::to_string((int)DEFAULT_SETTINGS.ball_size)), 18u, sf::Color::Black, sf::Color(100,100,100), sf::Color::White, sf::Color::White);
	y += spacing;

	texts.emplace_back(tbFont, sf::String("Ball max speed:"), 18u);
	texts.back().setFillColor(sf::Color::Black);
	texts.back().setPosition({ label_x, y });
	text_boxes.emplace_back(sf::Vector2f(input_x, y), sf::Vector2f(150.f, 40.f), tbFont, sf::String(std::to_string((int)DEFAULT_SETTINGS.ball_max_speed)), 18u, sf::Color::Black, sf::Color(100,100,100), sf::Color::White, sf::Color::White);
	y += spacing;

	texts.emplace_back(tbFont, sf::String("Ball starting speed:"), 18u);
	texts.back().setFillColor(sf::Color::Black);
	texts.back().setPosition({ label_x, y });
	text_boxes.emplace_back(sf::Vector2f(input_x, y), sf::Vector2f(150.f, 40.f), tbFont, sf::String(std::to_string((int)DEFAULT_SETTINGS.ball_default_speed)), 18u, sf::Color::Black, sf::Color(100,100,100), sf::Color::White, sf::Color::White);
	y += spacing;

	texts.emplace_back(tbFont, sf::String("Bounce speed increment:"), 18u);
	texts.back().setFillColor(sf::Color::Black);
	texts.back().setPosition({ label_x, y });
	text_boxes.emplace_back(sf::Vector2f(input_x, y), sf::Vector2f(150.f, 40.f), tbFont, sf::String(std::to_string((int)DEFAULT_SETTINGS.speedup)), 18u, sf::Color::Black, sf::Color(100, 100, 100), sf::Color::White, sf::Color::White);
	y += spacing;


	float group_spacing = 8.f;
	float btn_w = 100.f, btn_h = 30.f;
	float centerX = back.getPosition().x + back.getSize().x / 2.f;
	float col_gap = 220.f;
	float left_center_x = centerX - col_gap / 2.f;
	float right_center_x = centerX + col_gap / 2.f;
	float left_btn_x = left_center_x - btn_w / 2.f;
	float right_btn_x = right_center_x - btn_w / 2.f;
	float title_y = y;

	texts.emplace_back(tbFont, sf::String("Player 1 type"), 12u);
	texts.back().setFillColor(sf::Color::Black);
	{
		float w = texts.back().getGlobalBounds().size.x;
		texts.back().setPosition({ left_center_x - w / 2.f, title_y });
	}
	texts.emplace_back(tbFont, sf::String("Player 2 type"), 12u);
	texts.back().setFillColor(sf::Color::Black);
	{
		float w = texts.back().getGlobalBounds().size.x;
		texts.back().setPosition({ right_center_x - w / 2.f, title_y });
	}

	size_t left_sel_idx = texts.size();
	texts.emplace_back(tbFont, "", 12u);
	texts.back().setFillColor(sf::Color::Black);
	{
		float w = texts.back().getGlobalBounds().size.x;
		texts.back().setPosition({ left_center_x - w / 2.f, title_y + 18.f });
	}
	size_t right_sel_idx = texts.size();
	texts.emplace_back(tbFont, "", 12u);
	texts.back().setFillColor(sf::Color::Black);
	{
		float w = texts.back().getGlobalBounds().size.x;
		texts.back().setPosition({ right_center_x - w / 2.f, title_y + 18.f });
	}

	float btn_y = title_y + 40.f;
	const sf::Font& btnFont = asset_manager.get_font(BUTTON);
	// Player 1 buttons
	buttons.emplace_back(sf::Vector2f(left_btn_x, btn_y), sf::Vector2f(btn_w, btn_h), btnFont, "Mouse Player", 12u, [this, left_sel_idx]() { lplayer = MOUSEPLAYER; });
	buttons.emplace_back(sf::Vector2f(left_btn_x, btn_y + btn_h + group_spacing), sf::Vector2f(btn_w, btn_h), btnFont, "Bot", 12u, [this, left_sel_idx]() { lplayer = BOT;});
	buttons.emplace_back(sf::Vector2f(left_btn_x, btn_y + (btn_h + group_spacing) * 2), sf::Vector2f(btn_w, btn_h), btnFont, "Wall", 12u, [this, left_sel_idx]() { lplayer = WALL;});

	// Player 2 buttons
	buttons.emplace_back(sf::Vector2f(right_btn_x, btn_y), sf::Vector2f(btn_w, btn_h), btnFont, "Mouse Player", 12u, [this, right_sel_idx]() { rplayer = MOUSEPLAYER; });
	buttons.emplace_back(sf::Vector2f(right_btn_x, btn_y + btn_h + group_spacing), sf::Vector2f(btn_w, btn_h), btnFont, "Bot", 12u, [this, right_sel_idx]() { rplayer = BOT; });
	buttons.emplace_back(sf::Vector2f(right_btn_x, btn_y + (btn_h + group_spacing) * 2), sf::Vector2f(btn_w, btn_h), btnFont, "Wall", 12u, [this, right_sel_idx]() { rplayer = WALL; });
}
void SinglePlayerConfigMenu::process_imput() {
	while (const std::optional event = window.pollEvent()) {
		process_window_events(event, window);
		for (TextBox& tb : text_boxes) {
			tb.update_selected(window);
			tb.process_digit(*event);
		}
		if (!text_boxes.any([](const TextBox& tb) {return tb.is_selected();}) && event->is<sf::Event::KeyPressed>()) {
			if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
				state_manager.pop();
			}
		}
	}
	for(Button& button:buttons) button.update(window);
}
void SinglePlayerConfigMenu::update(sf::Time dt){
	switch (lplayer) {
	case MOUSEPLAYER:
		texts[texts.size()-2].setString("Mouse Player");break;
	case BOT:
		texts[texts.size()-2].setString("Bot");break;
	case WALL:
		texts[texts.size()-2].setString("Wall");break;
	}
	switch (rplayer) {
	case MOUSEPLAYER:
		texts[texts.size()-1].setString("Mouse Player");break;
	case BOT:
		texts[texts.size()-1].setString("Bot");break;
	case WALL:
		texts[texts.size()-1].setString("Wall");break;
	}
}
void SinglePlayerConfigMenu::draw(){
	window.clear(sf::Color::Black);
	window.draw(back);
	window.draw(title);
	for (const sf::Text& text : texts)
		window.draw(text);
	for (const TextBox& tb : text_boxes)
		window.draw(tb);
	for (const Button& button : buttons)
		window.draw(button);
	window.display();
}