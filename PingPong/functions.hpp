#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "GameplaySettings.hpp"
#include "Ball.hpp"
inline bool is_between(float val, float min, float max) {
    return val >= min && val <= max;
}

inline sf::Vector2f random_direction() { // Devuelve un vector al azar con norma raiz de 2 (para que la direccion no influya en la velocidad a la que se mueve la bola)
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(-SQRT2+0.2f, SQRT2-0.2f);// +- 0.3 para que la bola no salga tan vertical
	float y_direction = dis(gen);
	std::uniform_int_distribution<short> dis2(0, 1);
	return sf::Vector2f(dis2(gen) == 1 ? sqrtf(2 - y_direction * y_direction) : -sqrtf(2 - y_direction * y_direction),y_direction);
}

inline Ball throw_ball(const GameplaySettings& settings) {
    return Ball(settings);
}
inline void toggle_fullscreen(sf::RenderWindow& window) {
	static bool is_fullscreen = false;
	;
	if (is_fullscreen) {
		window.close();
		window.create(sf::VideoMode(sf::Vector2u(1920, 1080)), "Pong", sf::State::Windowed);
	}
	else {
		window.close();
		window.create(sf::VideoMode(sf::Vector2u(1920, 1080)), "Pong", sf::State::Fullscreen);
	}
	is_fullscreen = !is_fullscreen;
}
inline void process_window_events(const std::optional<sf::Event> event, sf::RenderWindow& window) {
	if (event->is<sf::Event::Closed>())
		window.close();
	if (event->is<sf::Event::KeyPressed>()) {
		if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::F11) {
			toggle_fullscreen(window);
		}
	}
}
