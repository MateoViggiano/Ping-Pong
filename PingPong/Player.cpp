#pragma once
#include <viggiano.hpp>
#include "Player.hpp"
#include "Ball.hpp"
#include <SFML/Graphics.hpp>

Player::Player(float height, float x, float y) :pos(x, y) {
	shape.setSize(sf::Vector2f(PLAYER_WIDTH, height));
	shape.setPosition(pos);
}
sf::RectangleShape Player::get_shape()const {
	return shape;
}
float Player::get_left()const {
	return pos.x;
}
float Player::get_right()const {
	return pos.x + shape.getSize().x;
}
float Player::get_middle_x()const {
	return pos.x + shape.getSize().x / 2;
}
float Player::get_middle_y()const {
	return pos.y + shape.getSize().y / 2;
}
float Player::get_top()const {
	return pos.y;
}
float Player::get_bottom()const {
	return pos.y + shape.getSize().y;
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(shape);
}
Player::~Player(){}
MousePlayer::MousePlayer(float height, float x, float y, const sf::RenderWindow& window): Player(height,x,y),window(window){}
void MousePlayer::update(const sf::Vector2f world) {
	pos.y = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y - shape.getSize().y / 2;
	if (pos.y < 0) pos.y = 0;
	else if (get_bottom() > world.y) pos.y = world.y - shape.getSize().y;
	shape.setPosition(pos);
}
Bot::Bot(float height,float x, float y, const mpv::Vector<Ball>& balls): Player(height,x,y),balls(balls){}

void Bot::update(const sf::Vector2f world) {
	sf::Vector2f nearest(float(world.x)/2.f,float(world.y)/2.f);
	for (const Ball& ball : balls) {
		if (mpv::abs(get_middle_x() - ball.get_middle_x()) < abs(get_middle_x() - nearest.x)) nearest = ball.get_position().getCenter();
	}
	pos.y = nearest.y - shape.getSize().y / 2;
	if (pos.y < 0) pos.y = 0;
	else if (get_bottom() > world.y) pos.y = world.y - shape.getSize().y;
	shape.setPosition(pos);
}
Wall::Wall(float x,float y, const sf::Vector2f world) :Player(world.y ,x , y) {}
void Wall::update(const sf::Vector2f) {}