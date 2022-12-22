#include <adder/StateMachine.hxx>

#include <iostream>

#include <adder/states/InitState.hxx>
#include <memory>

adder::StateMachine::StateMachine():
    is_running(true), state_chg_f(false)
{
    state = std::make_shared<InitState>(this);
}

void adder::StateMachine::update(){
    if(state_chg_f){
        state = state_to_be;

        state_chg_f=false;
    }
}

void adder::StateMachine::end(){
    is_running=false;
}

std::shared_ptr<adder::State>& adder::StateMachine::getCurrentState(){
    return state;
}

const bool& adder::StateMachine::isRunning(){
    return is_running;
}