#pragma once
#include <viggiano.hpp>
#include <SFML/Graphics.hpp>
class Ball;
constexpr float PLAYER_WIDTH = 14.f;
class Player : public sf::Drawable{
protected:
	sf::Vector2f pos;
	sf::RectangleShape shape;
public:
	Player(float, float, float);
	sf::RectangleShape get_shape()const;
	float get_left()const;
	float get_right()const;
	float get_middle_x()const;
	float get_middle_y()const;
	float get_top()const;
	float get_bottom()const;
	virtual void update(const sf::Vector2f) = 0;
	virtual ~Player();
	virtual void draw(sf::RenderTarget&, sf::RenderStates states)const override;
};

class MousePlayer :public Player {
	const sf::RenderWindow& window;
public:
	MousePlayer(float, float, float, const sf::RenderWindow&);
	void update(const sf::Vector2f)override;
};

class Bot :public Player {
	const mpv::Vector<Ball>& balls;
public:
	Bot(float, float, float, const mpv::Vector<Ball>&);
	void update(const sf::Vector2f)override;
};
class Wall :public Player {
public:
	using Player::Player;
	Wall(float,float, const sf::Vector2f);
	void update(const sf::Vector2f)override;
};