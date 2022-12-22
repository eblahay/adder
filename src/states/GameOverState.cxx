#include "adder/StateMachine.hxx"
#include <SFML/Window/Event.hpp>
#include <adder/states/GameOverState.hxx>
#include <adder/states/GameplayState.hxx>

#include <iostream>

adder::GameOverState::GameOverState(StateMachine* sm, std::default_random_engine& gen):
    State(sm), gen(gen)
{
    font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSerif-Bold.ttf");
				
				
    txt.setString("The Adder hath perished!\n\npress 'ENTER' to retry");
    txt.setFont(font);
    txt.setCharacterSize(48);
    txt.setFillColor({120, 120, 120});
}

void adder::GameOverState::handleInput(){
    sf::Event event;
    sm->window.pollEvent(event);
    switch(event.type){
        case sf::Event::Closed:
            sm->end();
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code){
                case sf::Keyboard::Enter:
                    // retry
                    sm->changeState<GameplayState>(gen);
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}

void adder::GameOverState::update(){

}

void adder::GameOverState::draw(){
    sm->window.draw(txt);
}