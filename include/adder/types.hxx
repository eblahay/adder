#pragma once

#include <array>

namespace adder {
    // class for storing coordinate values
    class Coord{
        public:
            Coord(int x, int y);

            bool operator==(const adder::Coord& b)const;

            int x, y;
    };
}