/*
    Game.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (Game.cpp) defines a constructor for the Game class
    and a terminateGame member function that asks the player
    if the game should end.
*/

// All includes
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Game.h"
#include "GlobalValues.h"

/*
    Definition of Game class constructor that add all of the input player's
    names to the names member vector variable.
*/
Game::Game(int argc, const char *argv[])
{
    for (int i = CMD_START_IDX; i < argc; ++i)
    {
        names.push_back(string(argv[i]));
    }
}

/*
    Definition of terminateGame that asks the user if they want to terminate
    the game or not.
*/
bool Game::terminateGame()
{
    cout << "Would you like to end the game? (yes/no): " << endl;
    string ans;
    cin >> ans;
    if (ans == "yes")
    {
        return true;
    }
    return false;
}