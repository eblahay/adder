#include "adder/types.hxx"
#include <adder/Snake.hxx>

adder::Snake::Snake(const adder::Coord &starting_coordinate):
    direction(down), is_dead(false), target(0,0)
{
    segments.push_back(starting_coordinate);
}

const std::vector<adder::Coord>& adder::Snake::getSegments()const{
    return segments;
}

const adder::Coord& adder::Snake::getTarget()const{
    return target;
}

const bool& adder::Snake::isDead()const{
    return is_dead;
}

void adder::Snake::update(){
    // update body
    for(int i=segments.size()-1; i > 0; i--){
        segments[i] = segments[i-1];
    }

    // update head
    segments[0] = getTarget();

    // update target
    setTarget();
}

void adder::Snake::kill(){
    is_dead = true;
}

void adder::Snake::grow(){

    int x=0, y=0;

    switch (direction) {
        case down:
            y=-1;
            break;
        case up:
            y=1;
            break;
        case right:
            x=-1;
            break;
        default:
            x=1;
            break;
    }

    segments.push_back({
        segments[0].x + x,
        segments[0].y + y
    });
}

void adder::Snake::turn(const Direction &direction){
    if(
        segments.size() < 2 ||
        this->direction != direction * -1
    ){
        this->direction = direction;
    }
}

void adder::Snake::setTarget(){
    int x=0, y=0;

    // figure out snake's target based on head coords & direction
    if(direction == down) y++;
    else if(direction == up) y--;
    else if(direction == right) x++;
    else x--;

    target = Coord(segments[0].x + x, segments[0].y + y);
}
