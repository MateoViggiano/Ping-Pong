#pragma once
#include "Menu.hpp"
#include "AssetManager.hpp"
#include "SinglePlayerConfigMenu.hpp"
#include "functions.hpp"
extern mpv::StateMachine<State> state_manager;
extern AssetManager asset_manager;

Menu::Menu(sf::RenderWindow& window) : State(window), title(asset_manager.get_font(TITLE), "Pong") {
	title.setCharacterSize(96);
	title.setFillColor(sf::Color::Black);
	sf::Vector2f winSize = window.getView().getSize();
	title.setPosition({ winSize.x / 2.f - 180.f, winSize.y * 0.2f });
	back.setFillColor(sf::Color(0,0,150));
	back.setSize({ 600.f,winSize.y * 0.8f});
	back.setPosition({winSize.x / 2.f - back.getSize().x / 2,winSize.y * 0.1f});
	
	buttons.emplace_back(sf::Vector2f(winSize.x / 2.f - 150.f, winSize.y * 0.35f), sf::Vector2f(300.f, 70.f), asset_manager.get_font(BUTTON), "Single Player",[&window]() {
		state_manager.push(new SinglePlayerConfigMenu(window));
	});
	buttons.emplace_back(sf::Vector2f(winSize.x / 2.f - 150.f, winSize.y * 0.45f), sf::Vector2f(300.f, 70.f), asset_manager.get_font(BUTTON), "Multiplayer", []() {
		
	});
	buttons.emplace_back(sf::Vector2f(winSize.x / 2.f - 150.f, winSize.y * 0.55f), sf::Vector2f(300.f, 70.f), asset_manager.get_font(BUTTON), "Exit", [&window]() {
		window.close();
	});
}

void Menu::process_imput() {
	while (const std::optional event = window.pollEvent()) {
		process_window_events(event, window);
	}
	for (Button& button : buttons) {
		button.update(window);
	}
}

void Menu::update(sf::Time dt) {}

void Menu::draw() {
	window.clear(sf::Color::Black);
	window.draw(back);
	window.draw(title);
	for (const Button& button : buttons)
		window.draw(button);
	window.display();
}

