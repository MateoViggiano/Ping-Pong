#pragma once
#include "Pause.hpp"
#include "AssetManager.hpp"
#include "functions.hpp"
#include "SinglePlayerConfigMenu.hpp"

extern mpv::StateMachine<State> state_manager;
extern AssetManager asset_manager;

Pause::Pause(sf::RenderWindow& window) : State(window), title(asset_manager.get_font(TITLE), "Paused") {
	title.setCharacterSize(72);
	title.setFillColor(sf::Color::White);
	sf::Vector2f winSize = window.getView().getSize();
	title.setPosition({ winSize.x / 2.f - 200.f, winSize.y * 0.2f });
	back.setFillColor(sf::Color(50,50,50,200));
	back.setSize({ 600.f,winSize.y * 0.6f});
	back.setPosition({winSize.x / 2.f - back.getSize().x / 2,winSize.y * 0.15f});

	buttons.emplace_back(sf::Vector2f(winSize.x / 2.f - 150.f, winSize.y * 0.35f), sf::Vector2f(300.f, 70.f), asset_manager.get_font(BUTTON), "Resume", [&window]() {
		state_manager.pop();
	});
	buttons.emplace_back(sf::Vector2f(winSize.x / 2.f - 150.f, winSize.y * 0.45f), sf::Vector2f(300.f, 70.f), asset_manager.get_font(BUTTON), "Exit to Menu", [&window]() {
		state_manager.pop_until_find<SinglePlayerConfigMenu>();
	});
}

void Pause::process_imput() {
	while (const std::optional event = window.pollEvent()) {
		process_window_events(event, window);
		if (event->is<sf::Event::KeyPressed>()) {
			if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
				state_manager.pop();
			}
		}
	}
	for (Button& button : buttons) {
		button.update(window);
	}
}

void Pause::update(sf::Time dt) {}

void Pause::draw() {
	window.clear(sf::Color(0,0,0,0));
	window.draw(back);
	window.draw(title);
	for (const Button& button : buttons)
		window.draw(button);
	window.display();
}
