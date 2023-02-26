#pragma once

#include <random>

#include <SFML/Graphics/RectangleShape.hpp>

#include <adder/State.hxx>
#include <adder/Snake.hxx>

namespace adder {
    struct Arena{
		const unsigned int
			WIDTH=28,
			HEIGHT=28,

			X=0, Y=0 // arena position within window
		;
	};

    /*
        the state representing gameplay
    */
    class GameplayState: public State{
        public:
            GameplayState(StateMachine* sm, std::default_random_engine& gen);

            void handleInput();

            void update();

            void draw();
        private:
            const Arena ARENA;
            Snake snake;
            Coord food;
            // RNG
            std::default_random_engine& gen;
            std::uniform_int_distribution<unsigned int> dist;

            float cnt;// count
    };
}