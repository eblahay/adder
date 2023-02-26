#include <adder/states/GameplayState.hxx>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <adder/states/GameOverState.hxx>

adder::GameplayState::GameplayState(adder::StateMachine* sm, std::default_random_engine& gen):
    State(sm),
    snake({0,0}),
    gen(gen),
    dist(1, ARENA.WIDTH-2),
    food(0,0)
{
    // set food's initial position
    food.x = dist(gen);
    food.y = dist(gen);

    // limit framerate (this is called here to prevent input slow-down in other states)
    sm->window.setFramerateLimit(16);
}

adder::GameplayState::~GameplayState(){
    // change fps limit back to 60 (to avoid input slowdown in other states)
    sm->window.setFramerateLimit(60);
}

void adder::GameplayState::handleInput(){
    sf::Event event;
    while(sm->window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                sm->end();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        //paused = !paused;
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
}

void adder::GameplayState::update(){
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

            // move food to new spot
            food = {
                dist(gen),
                dist(gen)
            };
        }
    }

    // change to Game Over if necessary
    if(snake.isDead()) sm->changeState<GameOverState>(gen);
}

void adder::GameplayState::draw(){
    sm->window.clear();

    // draw food
    sf::RectangleShape food_rect;
    food_rect.setSize({20,20});
    food_rect.setFillColor(sf::Color::Yellow);

    food_rect.setPosition({
        (float)food.x*20 + ARENA.X,
        (float)food.y*20 + ARENA.Y
    });

    sm->window.draw(food_rect);

    // draw snake
    for(auto it=snake.getSegments().begin(); it != snake.getSegments().end(); it++){
        sf::RectangleShape r;
        r.setSize({20,20});
        r.setFillColor(sf::Color::White);

        r.setPosition({
            (float)(*it).x*20 + ARENA.X,
            (float)(*it).y*20 + ARENA.Y
        });

        sm->window.draw(r);
    }
}