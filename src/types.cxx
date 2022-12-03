#include <adder/types.hxx>

adder::Coord::Coord(unsigned int x, unsigned int y):
    x(x), y(y)
{}

bool adder::Coord::operator==(const adder::Coord &b)const{
    return (x == b.x && y == b.y);
}