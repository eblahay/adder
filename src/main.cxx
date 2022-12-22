#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <adder/types.hxx>
#include <adder/Snake.hxx>
#include <utility>
#include <vector>
#include <map>
#include <random>
#include <chrono>

#include <adder/config.h>

#include <adder/StateMachine.hxx>
#include <adder/states/GameplayState.hxx>

int main(int argc, char* argv[]){
	// prep & seed RNG
	std::default_random_engine gen(
		std::chrono::system_clock::now().time_since_epoch().count()
	);

	// create state machine
	adder::StateMachine sm;

	// prep window
	std::string title_str("The Adder v");
	title_str.append(PROJ_VER);
	sm.window.create({560,560}, title_str);

	sm.window.setFramerateLimit(16);
	///

	// add initial state
	sm.setState<adder::GameplayState>(gen);
	
	// gameploop
	while(sm.isRunning()){
		sm.getCurrentState().get()->handleInput();
		sm.getCurrentState().get()->update();
		sm.getCurrentState().get()->draw();

		sm.window.display();
	
		sm.update();
	}

	if(sm.window.isOpen()) sm.window.close();
	
	return 0;
}
