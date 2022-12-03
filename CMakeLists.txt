cmake_minimum_required(VERSION 3.22)

# set project name
project(adder VERSION "0.2.0")

# specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# config config header
configure_file(src/config.h.in include/adder/config.h)

# grab libaries
find_package(SFML COMPONENTS window graphics system)

# set up executable
set(
    SRC
    src/main.cxx
    src/Snake.cxx
    src/types.cxx
)
add_executable(adder ${SRC})
target_link_libraries(adder sfml-window sfml-graphics sfml-system)

# include directories must come AFTER the executable's been added
include_directories(include build/include)
