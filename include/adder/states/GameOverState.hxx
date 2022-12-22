#pragma once

#include <SFML/Graphics/Text.hpp>
#include <adder/State.hxx>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <random>

namespace adder {
    /*
        the state representing a game over
    */
    class GameOverState: public State{
        public:
            GameOverState(StateMachine* sm, std::default_random_engine& gen);

            void handleInput();

            void update();

            void draw();
        private:
            sf::Font font;
            sf::Text txt;

            // for retry
            std::default_random_engine& gen;
    };
}