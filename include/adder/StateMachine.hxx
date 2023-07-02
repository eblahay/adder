#pragma once

#include <cstddef>
#include <vector>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace adder {
    class State; // foward decl

    class StateMachine{
        public:
            StateMachine();

            template<typename T, typename... Args>
            void setState(Args&&... args){
                state = std::make_shared<T>(this, args...);
            }
            
            // clear the state stack and push the specified state
            template<typename T, typename... Args>
            void changeState(Args&&... args){
                state_chg_f=true;
                state_to_be = std::make_shared<T>(this, args...);
            }

            void update();

            // end the gameloop
            void end();

            // return a reference to the current state
            std::shared_ptr<State>& getCurrentState();

            // return current delta-time (in seconds)
            const float& getDeltaTime()const;

            const bool& isRunning();

            sf::RenderWindow window;
        private:
            std::shared_ptr<State> state;
            std::shared_ptr<State> state_to_be; // var to hold the next state while prepping a state change

            // var rep. which dictates whether the 
            // gameloop is running
            bool is_running, state_chg_f;

            sf::Clock clock;
            float dt; // delta-time; the amt of time between this frame and the last
            
    };
}