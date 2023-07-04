#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <adder/states/GameplayState.hxx>

#include <iterator>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <adder/states/GameOverState.hxx>
#include <adder/Snake.hxx>
#include <sstream>

adder::GameplayState::GameplayState(adder::StateMachine* sm, std::default_random_engine& gen):
    State(sm),
    snake({0,0}),
    gen(gen),
    dist(1, ARENA.WIDTH-2),
    food(0,0),
    cnt(0),
    TILE_LEN(20)
{
    // set food's initial position
    food.x = dist(gen);
    food.y = dist(gen);

    // load textures
    food_txtr.loadFromFile("../data/assets/food.png"); // change path later
    snake_txtr.loadFromFile("../data/assets/snake.png");

    // load sprites
    food_spt.setTexture(food_txtr);
    snake_spt.setTexture(snake_txtr);
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
    
    if(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::S)
    ){
        snake.turn(adder::down);
    }
    else if(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::W)
    ){
        snake.turn(adder::up);
    }
    else if(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::D)
    ){
        snake.turn(adder::right);
    }
    else if(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::A)
    ){
        snake.turn(adder::left);
    }
}

void adder::GameplayState::update(){
    // counter code; staggers snake collision update to ~12fps (60 / 5)
    // basic exec pattern: 0 (snake updates) -> 1 -> 2 -> 3 -> 4 (reset counter) -> [repeat]
    if(cnt >= 1.f) cnt = 0.f;
    
    if(cnt == 0.f) snake.update();
    cnt += 12 * sm->getDeltaTime();
    
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
    sm->window.clear({24,100,0});

    // draw food
    food_spt.setPosition({
        (float)food.x * TILE_LEN + ARENA.X,
        (float)food.y * TILE_LEN + ARENA.Y
    });

    sm->window.draw(food_spt);

    // draw snake
    
    // draw head
    switch(snake.getDirection()){
        case up:
            snake_spt.setTextureRect({0,0, 20,20});
            break;
        case down:
            snake_spt.setTextureRect({20,0, 20,20});
            break;
        case left:
            snake_spt.setTextureRect({40,0, 20,20});
            break;
        case right:
            snake_spt.setTextureRect({60,0, 20,20});
            break;
        default:
            snake_spt.setTextureRect({0,0, 20,20});
            break;
    }
    snake_spt.setPosition({
        (((float)(*snake.getSegments().begin()).x) + ((float)(snake.getTarget().x - (*snake.getSegments().begin()).x) * cnt)) * TILE_LEN + ARENA.X,
        (((float)(*snake.getSegments().begin()).y) + ((float)(snake.getTarget().y - (*snake.getSegments().begin()).y) * cnt)) * TILE_LEN + ARENA.Y
    });
    sm->window.draw(snake_spt);

    // draw tail
    snake_spt.setTextureRect({0,20, 20,20});

    for(auto it=snake.getSegments().begin()+1; it != snake.getSegments().end(); it++){
        snake_spt.setPosition({
            (((float)(*it).x) + ((float)(std::prev(it)->x - (*it).x) * cnt)) * TILE_LEN + ARENA.X,
            (((float)(*it).y) + ((float)(std::prev(it)->y - (*it).y) * cnt)) * TILE_LEN + ARENA.Y
        });

        sm->window.draw(snake_spt);
    }
}