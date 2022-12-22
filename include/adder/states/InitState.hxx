#pragma once

#include <adder/State.hxx>

namespace adder {
    class InitState: public State{
        public:
            InitState(StateMachine* sm);

            void handleInput();

            void update();

            void draw();
    };
}