/*
    Game.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (Game.h) declares a Game class with two public
    member functions, a protected member variable,
    and a protected member function.
*/

// All includes
#pragma once

#include <string>
#include <vector>

/*
    Declaration of the Game class which has a public constructor
    and pure virtual function. As well as a protected names member variable
    vector and a terminateGame protected member function.
*/
class Game
{
public:
    Game(int argc, const char *argv[]);
    virtual int play() = 0;

protected:
    std::vector<std::string> names;
    bool terminateGame();
};