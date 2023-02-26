#pragma once

#include <adder/StateMachine.hxx>

namespace adder {
    /*
        A base class for the Program's states of execution
        (each state will be reprsented w/ a subclass of this)
    */
    class State{
        public:
            State(StateMachine* sm){
                this->sm = sm;
            }

            virtual void handleInput() = 0;

            virtual void update() = 0;

            virtual void draw() = 0;

        protected:
            StateMachine* sm;
    };
}