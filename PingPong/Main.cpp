#include<cassert>
#include<Windows.h>
#include <SFML/Graphics.hpp>
#include <viggiano.hpp>
#include "AssetManager.hpp"
#include "Menu.hpp"


mpv::StateMachine<State> state_manager;
AssetManager asset_manager;
int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Pong", sf::State::Windowed);
    asset_manager.add_font(TITLE, "C:/Windows/Fonts/vinet.ttf");
    asset_manager.add_font(TEXTBOX, "C:/Windows/Fonts/YuGothR.ttc");
    asset_manager.add_font(BUTTON, "C:/Windows/Fonts/YuGothB.ttc");

    sf::Clock clk;
    state_manager.push(new Menu(window));
    sf::Time dt;
    while (window.isOpen()) {
        dt = clk.restart();
        printf("FPS: %f\n", 1.f/dt.asSeconds());
        window.clear();
        state_manager.process_change();
        state_manager.current().process_imput();
        state_manager.current().update(dt);
        state_manager.current().draw();
        
    }
}