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

            // output the current targeted destination for the snake's head
            const Coord& getTarget()const;

            // get snake's current direction
            const Direction& getDirection()const;

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
            // set the alters the target value
            void setTarget();

            /*
                a collection of the coordinates which make up the snake's segments
            */
            std::vector<Coord> segments;

            Coord target;

            Direction direction;

            bool is_dead;
    };
}
