#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <adder/StateMachine.hxx>
#include <adder/states/TitlescreenState.hxx>
#include <adder/states/GameplayState.hxx>
#include <adder/config.h>

adder::TitlescreenState::TitlescreenState(adder::StateMachine* sm, std::default_random_engine& gen):
    State(sm), gen(gen)
{
    font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSerif-Bold.ttf");

    title_txt.setString("The Adder");
    title_txt.setFont(font);
    title_txt.setCharacterSize(64);
    title_txt.setPosition(
        (sm->window.getSize().x / 2.f)-(title_txt.getGlobalBounds().width/2),
        (sm->window.getSize().y / 2.f)-(title_txt.getGlobalBounds().height/2)
    );
    title_txt.setFillColor({255,255,255});

    std::string ver_a = "version ";
    ver_a.append(PROJ_VER);
    ver_txt.setString(ver_a);
    ver_txt.setFont(font);
    ver_txt.setCharacterSize(12);
    ver_txt.setPosition(
        (sm->window.getSize().x - ver_txt.getGlobalBounds().width - 8),
        (sm->window.getSize().y - ver_txt.getGlobalBounds().height - 8)
    );
    ver_txt.setFillColor({255,255,255});
}

void adder::TitlescreenState::handleInput(){
    sf::Event event;
    sm->window.pollEvent(event);
    switch(event.type){
        case sf::Event::Closed:
            sm->end();
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code){
                case sf::Keyboard::Enter:
                    sm->changeState<GameplayState>(gen);
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}

void adder::TitlescreenState::update(){
    
}

void adder::TitlescreenState::draw(){
    sm->window.clear();
    sm->window.draw(title_txt);
    sm->window.draw(ver_txt);
}