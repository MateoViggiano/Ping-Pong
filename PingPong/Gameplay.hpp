#pragma once
#include "State.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "GameplaySettings.hpp"
class Gameplay:public State {
private:
	const GameplaySettings settings;
	mpv::Vector<Ball> balls;
	mpv::uPtr<Player> lplayer,rplayer;
	sf::Clock timer;
	sf::Time elapsed;
public:
	Gameplay(sf::RenderWindow&, const GameplaySettings&);
	void process_imput()override;
	void update(sf::Time dt)override;
	void draw()override;
	void enter()override;
	void exit()override;
};
