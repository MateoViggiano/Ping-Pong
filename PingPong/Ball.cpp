#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Player.hpp"
#include<random>
#include <cmath>
#include <cstdint>
#include "functions.hpp"
Ball::Ball(const GameplaySettings& settings):settings(settings), pos(settings.world_size.x / 2 - settings.ball_size/2, settings.world_size.y / 2 - settings.ball_size / 2), speed(settings.ball_default_speed) {
	shape.setSize(sf::Vector2f(settings.ball_size, settings.ball_size));
	shape.setPosition(pos);
	direction = random_direction();
	trail.insert_at(0, 50, pos + shape.getGeometricCenter());
}
sf::FloatRect Ball::get_position()const {
	return shape.getGlobalBounds();
}
float Ball::get_left()const {
	return pos.x;
}
float Ball::get_right()const {
	return pos.x + shape.getSize().x;
}
float Ball::get_top()const {
	return pos.y;
}
float Ball::get_bottom()const {
	return pos.y + shape.getSize().y;
}
float Ball::get_middle_x()const {
	return pos.x + shape.getSize().x / 2;
}
float Ball::get_middle_y()const {
	return pos.y + shape.getSize().y / 2;
}
sf::RectangleShape Ball::get_shape()const {
	return shape;
}
void Ball::bounce_y() {
	direction.y = -direction.y;
}
void Ball::bounce_x() {
	direction.x = -direction.x;
}
void Ball::speedup() {
	if (speed < settings.ball_max_speed) speed += settings.speedup;
	//printf("ball speed: %f\n",speed);
}
void Ball::update(sf::Time dt) {
	pos.x += direction.x * speed * dt.asSeconds();
	pos.y += direction.y * speed * dt.asSeconds();
	shape.setPosition(pos);
}
void Ball::update_trial() {
	trail.insert_at(0,pos + shape.getGeometricCenter());
	trail.del_back();
}
void Ball::fix_collision_y() {
	if (pos.y < 0) {
		pos.y = 0;
	}
	else if (get_bottom() > settings.world_size.y) {
		pos.y = settings.world_size.y - shape.getSize().y;
	}
}
void Ball::fix_collision_x() {
	if (pos.x < 0) {
		pos.x = 0;
	}
	else if (get_right() > settings.world_size.x) {
		pos.x = settings.world_size.x - shape.getSize().x;
	}
}
void Ball::fix_collision(const Player& player) {
	if (is_between(get_right(), player.get_left(), player.get_middle_x())) {
		pos.x = player.get_left() - shape.getSize().x;
	}
	if (is_between(get_left(), player.get_middle_x(), player.get_right())) {
		pos.x = player.get_right();
	}
}
bool Ball::is_coliding(const Player& player)const {
	return (is_between(get_right(), player.get_left(), player.get_right()) || is_between(get_left(), player.get_left(), player.get_right())) && (is_between(get_bottom(), player.get_top(), player.get_bottom()) || is_between(get_top(), player.get_top(), player.get_bottom()));
}
void Ball::reset() {
	pos = sf::Vector2f(settings.world_size.x / 2 - settings.ball_size / 2, settings.world_size.y / 2 - settings.ball_size / 2);
	shape.setPosition(pos);
	speed = settings.ball_default_speed;
	direction = random_direction();
}
void Ball::randomize() {
	direction.x = direction.x >= 0.f ? 1.f : -1.f;
	direction.y = direction.y > 0.f ? 1.f : -1.f;
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(0.4f, SQRT2);
	direction.x *= dis(gen);
	direction.y *= sqrtf(2 - direction.x * direction.x);
}
void Ball::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(shape, states);
	//for (const sf::Vector2f v : trail) {
	//	temp.setOrigin(temp.getGeometricCenter());
	//	temp.setPosition(v);
	//	temp.setSize(temp.getSize() * 0.95f);
	//	target.draw(temp);
	//}
	// Construimos un único sf::VertexArray (TRIANGLES) con todos los rectángulos del trail
	// para enviarlo en una única llamada a la GPU. En SFML 3 los QUADS ya no existen,
	// así que representamos cada rectángulo como dos triángulos (6 vértices). Usar dos
	// triángulos es la forma estándar en GPU para dibujar rectángulos y no cambia
	// visualmente la pelota, solo reduce draw calls.
	sf::VertexArray verts(sf::PrimitiveType::Triangles);

	const sf::Vector2f baseSize = shape.getSize();

	const float sizeStep = 0.92f;
	const float alphaStep = 0.85f;

	std::size_t i = 0;
	for (const sf::Vector2f& center : trail) {
		const float fSize = std::pow(sizeStep, static_cast<float>(i));
		const sf::Vector2f half = (baseSize * fSize) * 0.5f;


		// Dos triángulos que conforman el rectángulo (orden: TL, TR, BR) y (TL, BR, BL)
		const sf::Vector2f tl(center.x - half.x, center.y - half.y);
		const sf::Vector2f tr(center.x + half.x, center.y - half.y);
		const sf::Vector2f br(center.x + half.x, center.y + half.y);
		const sf::Vector2f bl(center.x - half.x, center.y + half.y);

		verts.append(sf::Vertex(tl)); // triangle 1
		verts.append(sf::Vertex(tr));
		verts.append(sf::Vertex(br));

		verts.append(sf::Vertex(tl)); // triangle 2
		verts.append(sf::Vertex(br));
		verts.append(sf::Vertex(bl));

		++i;
	}

	//if (verts.getVertexCount() > 0) {
	//	target.draw(verts, states);
	//}
}