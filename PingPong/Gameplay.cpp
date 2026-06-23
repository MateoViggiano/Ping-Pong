#pragma once
#include "Gameplay.hpp"
#include "functions.hpp"
#include "Pause.hpp"
extern mpv::StateMachine<State> state_manager;

Gameplay::Gameplay(sf::RenderWindow& window, const GameplaySettings& settings) :State(window), settings(settings){
    settings.print();
    timer.start();
    balls.push_back(throw_ball(this->settings));
    switch (settings.rplayer) {
    case MOUSEPLAYER:
        rplayer = new MousePlayer(settings.player_heigth, settings.world_size.x - 50.f - PLAYER_WIDTH, 0, window);break;
    case BOT:
        rplayer = new Bot(settings.player_heigth, settings.world_size.x - 50.f - PLAYER_WIDTH, 0, balls);break;
    case WALL:
        rplayer = new Wall(settings.world_size.y, settings.world_size.x - 50.f - PLAYER_WIDTH, 0);break;
    }
    switch (settings.lplayer) {
    case MOUSEPLAYER:
        lplayer = new MousePlayer(settings.player_heigth, 50, 0, window);break;
    case BOT:
        lplayer = new Bot(settings.player_heigth, 50, 0, balls);break;
    case WALL:
        lplayer = new Wall(settings.world_size.y, 50, 0);break;
    }
}
void Gameplay::process_imput() {
    while (const std::optional event = window.pollEvent()) {
        process_window_events(event,window);
        if (event->is<sf::Event::KeyPressed>()) {
            if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                state_manager.push(new Pause(window));
            }
        }
    }
}
void Gameplay::update(sf::Time dt) {
    if (balls.size() < settings.ball_max && timer.getElapsedTime() >= settings.new_ball_time) {
        timer.restart();
        balls.push_back(throw_ball(settings));
    }
    rplayer->update(settings.world_size);
    lplayer->update(settings.world_size);
    unsigned steps = 1u + unsigned((dt.asSeconds() * settings.ball_max_speed) / std::min(settings.ball_size, PLAYER_WIDTH));
    printf("steps per frame: %u\n", steps);
    for(unsigned i = 0; i < steps; i++){
        sf::Time sub_dt = sf::seconds(dt.asSeconds() / steps);
        for (Ball& ball : balls) {
            ball.update(sub_dt);
            if (ball.is_coliding(*rplayer)) {
                ball.bounce_x();
                ball.randomize();
                ball.fix_collision(*rplayer);
                ball.speedup();
            }
            if (ball.is_coliding(*lplayer)) {
                ball.bounce_x();
                ball.randomize();
                ball.fix_collision(*lplayer);
                ball.speedup();
            }
            if (ball.get_top() <= 0 || ball.get_bottom() >= settings.world_size.y) {
                ball.bounce_y();
                ball.fix_collision_y();
            }
            if (ball.get_left() <= 0) {
                ball.reset();
                state_manager.pop();
                puts("Right Player wins");
            }
            if (ball.get_right() >= settings.world_size.x) {
                ball.reset();
                state_manager.pop();
                puts("Left Player wins");
            }
        }
    }
}
void Gameplay::draw() {
    for (Ball& ball : balls) {
        assert(ball.get_top() >= 0 && ball.get_bottom() <= settings.world_size.y);// Las pelotas nunca deberian atravezar un borde horizontal
        ball.update_trial();
        window.draw(ball);
    }
    window.draw(*rplayer);
    window.draw(*lplayer);
    window.display();
}
void Gameplay::enter() {}
void Gameplay::exit() {}