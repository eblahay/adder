#pragma once

#include <SFML/Graphics/Text.hpp>
#include <adder/State.hxx>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <random>

namespace adder {
    /*
        the state representing the titlescreen
    */
    class TitlescreenState: public State{
        public:
            TitlescreenState(StateMachine* sm, std::default_random_engine& gen);

            void handleInput();

            void update();

            void draw();
        private:
            sf::Font font;
            sf::Text title_txt, ver_txt;
            std::default_random_engine& gen;
    };
}