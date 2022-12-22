#include "adder/StateMachine.hxx"
#include <adder/states/InitState.hxx>

adder::InitState::InitState(adder::StateMachine* sm):
    State(sm)
{}

void adder::InitState::handleInput(){}

void adder::InitState::update(){
    sm->end();
}

void adder::InitState::draw(){}