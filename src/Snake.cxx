#include <adder/Snake.hxx>

adder::Snake::Snake(const adder::Coord &starting_coordinate):
    direction(down), is_dead(false)
{
    segments.push_back(starting_coordinate);
}

const std::vector<adder::Coord>& adder::Snake::getSegments()const{
    return segments;
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
    if(direction == down) segments[0].y++;
    else if(direction == up) segments[0].y--;
    else if(direction == right) segments[0].x++;
    else segments[0].x--;
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
