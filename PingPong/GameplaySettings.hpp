#pragma once
#include<SFML/Graphics.hpp>
enum PlayerType:char{MOUSEPLAYER,BOT,WALL};
struct GameplaySettings {
	sf::Vector2f world_size = sf::Vector2f(1920.f, 1080.f);
	sf::Time new_ball_time;
	size_t ball_max;
	float player_heigth;
	float ball_size;
	float ball_max_speed;
	float ball_default_speed;
	float speedup;
	PlayerType lplayer, rplayer;
	constexpr GameplaySettings(sf::Time new_ball_time, size_t ball_max, float player_heigth, float ball_size, float ball_max_speed, float ball_default_speed, float speedup, PlayerType lplayer,PlayerType rplayer) :new_ball_time(new_ball_time), ball_max(ball_max), player_heigth(player_heigth), ball_size(ball_size), ball_max_speed(ball_max_speed), ball_default_speed(ball_default_speed), speedup(speedup), lplayer(lplayer), rplayer(rplayer) {}
	constexpr GameplaySettings(const GameplaySettings&) = default;
	void print()const{
		printf("world_size: (%f,%f)\nnew_ball_time: %f\nball_max: %llu\nplayer_height: %f\nball_size: %f\nball_max_speed: %f\nball_default_speed: %f\nspeedup: %f\n",world_size.x,world_size.y,new_ball_time.asSeconds(),ball_max,player_heigth,ball_size,ball_max_speed,ball_default_speed,speedup);
	}
};