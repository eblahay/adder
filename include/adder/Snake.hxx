#pragma once

#include <vector>

#include <adder/types.hxx>

namespace adder {
    enum Direction {up=-1, down=1, left=-2, right=2};

    class Snake{
        public:
            Snake(const Coord &starting_coordinate);

            // get segment info
            const std::vector<Coord>& getSegments()const;

            // figure out if snake is dead (used to determine GAME OVER)
            const bool& isDead()const;

            // update snake movement
            void update();

            // kill the snake; make the snake dead.
            void kill();

            // add a segment to the snake
            void grow();

            // make the snake turn
            void turn(const Direction &direction);

        private:
            /*
                a collection of the coordinates which make up the snake's segments
            */
            std::vector<Coord> segments;

            Direction direction;

            bool is_dead;
    };
}
