#pragma once
#include <SFML/Graphics.hpp>
#include "GameplaySettings.hpp"
#include <viggiano.hpp>
//#include "Player.hpp"
class Player;
constexpr float SQRT2 = 1.41421356f;
class Ball: public sf::Drawable{
private:
	const GameplaySettings& settings;
	sf::Vector2f pos;
	sf::Vector2f direction;
	sf::RectangleShape shape;
	float speed;
	mpv::Vector<sf::Vector2f> trail;
public:
	Ball(const GameplaySettings&);
	sf::FloatRect get_position()const;
	float get_left()const;
	float get_right()const;
	float get_top()const;
	float get_bottom()const;
	float get_middle_x()const;
	float get_middle_y()const;
	sf::RectangleShape get_shape()const;
	void bounce_y();
	void bounce_x();
	void speedup();
	void update(sf::Time dt);
	void update_trial();
	void fix_collision_y();
	void fix_collision_x();
	void fix_collision(const Player& player);
	bool is_coliding(const Player& player)const;
	void reset();
	void randomize();
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const override;
};