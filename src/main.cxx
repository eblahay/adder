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

// function which contains the gameloop
int gameloop(sf::RenderWindow &window);

int main(int argc, char* argv[]){
	sf::RenderWindow window;
	window.create({560,560}, "The Adder");

	window.setFramerateLimit(24);

	while(gameloop(window) != 0);
	window.close();
	
	return 0;
}

int gameloop(sf::RenderWindow &window){
	
	// arena bounds
	struct Arena{
		const unsigned int
			WIDTH=28,
			HEIGHT=28,

			X=0, Y=0 // arena position within window
		;
	};
	const Arena ARENA;

	adder::Snake snake({0, 0});

	// set up food
	std::default_random_engine gen(6);
	std::uniform_int_distribution<unsigned int> dist(1,26);

	adder::Coord food(
		dist(gen),
		dist(gen)
	);

	while(window.isOpen()){
		sf::Event event;
        while (window.pollEvent(event)){
        	switch(event.type){
				case sf::Event::Closed:
					return 0;
					break;
				case sf::Event::KeyPressed:
					switch(event.key.code){
						case sf::Keyboard::F:
							snake.grow();
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
        }

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			snake.turn(adder::down);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			snake.turn(adder::up);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			snake.turn(adder::right);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			snake.turn(adder::left);
		}

		if(snake.isDead()){
			/*
				"Game Over" State
			*/

			sf::Font font;
			font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSerif-Bold.ttf");
			
			sf::Text txt;
			txt.setString("The Adder hath perished!\n\npress 'ENTER' to retry");
			txt.setFont(font);
			txt.setCharacterSize(48);
			txt.setFillColor(sf::Color::Red);

			window.draw(txt);
			window.display();
			
			while(true){
				window.pollEvent(event);
				switch(event.type){
					case sf::Event::Closed:
						return 0;
						break;
					case sf::Event::KeyPressed:
						switch(event.key.code){
							case sf::Keyboard::Enter:
								return 1;
								break;
							default:
								break;
						}
					default:
						break;
				}
			}
		}
		else{
			window.clear();

			// draw food
			sf::RectangleShape food_rect;
			food_rect.setSize({20,20});
			food_rect.setFillColor(sf::Color::Yellow);

			food_rect.setPosition({
				(float)food.x*20 + ARENA.X,
				(float)food.y*20 + ARENA.Y
			});

			window.draw(food_rect);

			// draw snake
			for(auto it=snake.getSegments().begin(); it != snake.getSegments().end(); it++){
				sf::RectangleShape r;
				r.setSize({20,20});
				r.setFillColor(sf::Color::White);

				r.setPosition({
					(float)(*it).x*20 + ARENA.X,
					(float)(*it).y*20 + ARENA.Y
				});

				window.draw(r);
			}

			window.display();

			// update snake
			snake.update();

			// chk snake collision
			if(
				snake.getSegments()[0].y < 0 ||
				snake.getSegments()[0].y >= ARENA.HEIGHT ||
				snake.getSegments()[0].x < 0 || 
				snake.getSegments()[0].x >= ARENA.WIDTH
			) snake.kill();
			else{

				for(auto it=snake.getSegments().begin()+1; it!=snake.getSegments().end(); it++){
					if(snake.getSegments()[0] == (*it)){
						snake.kill();
						break;
					}
				}

				if(snake.getSegments()[0] == food){
					snake.grow();

					food = {
						dist(gen),
						dist(gen)
					};
				}
			}
		}
	}

	return 0;
}
