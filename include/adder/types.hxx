#pragma once

#include <array>

namespace adder {
    // class for storing coordinate values
    class Coord{
        public:
            Coord(unsigned int x, unsigned int y);

            bool operator==(const adder::Coord& b)const;

            unsigned int x, y;
    };
}