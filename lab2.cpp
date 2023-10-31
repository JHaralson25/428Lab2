/*
    lab1.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (lab1.cpp) contains a function definition that creates
    a pointer to a class of the corresponding game class. It
    also contains "main" the driver function for Pinochle
    or HoldEm with validates command line input, creates the
    game and plays the game.
*/

// All includes
#include <iostream>
#include <memory>
#include <string>
#include <cstring>
using namespace std;

#include "HoldEmDeck.h"
#include "PinochleDeck.h"
#include "Game.h"
#include "HoldEmGame.h"
#include "GlobalValues.h"
#include "PinochleGame.h"

/*
    Method that returns an appropriate sharfed pointer for the Game class
    base on the user command line input.
*/
shared_ptr<Game> create(int argc, const char *argv[])
{
    shared_ptr<Game> game_pointer;

    // Check if Pinochle is the desired game
    if (strcmp(argv[CMD_GAME_IDX], PINOCHLE_NAME_STR) == 0)
    {
        game_pointer = make_shared<PinochleGame>(argc, argv);
    }
    // Check if HoldEM is the desired game
    else if (strcmp(argv[CMD_GAME_IDX], HOLD_EM_NAME_STR) == 0)
    {
        game_pointer = make_shared<HoldEmGame>(argc, argv);
    }
    // In the case where there is improper input, return a nullptr to be used for future reference
    else
    {
        game_pointer = nullptr;
    }
    return game_pointer;
}

/*
    Main method to play Pinochle or HoldEm. Contains return messages,
    parses command line input, checks game specific user parameters,
    and attempts to play the game. Returns appropriate return values
    at every stage.
*/
int main(int argc, const char *argv[])
{
    // Usage and error messages for the program
    string usage_msg = ("Usage: " + string(argv[CMD_PROG_IDX]) + " <gametype> (" + PINOCHLE_NAME_STR + " / " +
                        HOLD_EM_NAME_STR + ") <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)");
    string make_error_msg = "Failed to make game";

    // Checking that there is enough command line inputs supplied
    if (argc < CMD_START_IDX)
    {
        cout << usage_msg << endl;
        return IMPROPER_GAME_INPUT;
    }

    // Calculating the number of players
    int num_players = argc - CMD_START_IDX;

    /*
        Checking that if pinochle is the desired game, the correct number of
        players are supplied, and if not  print out usage message and return
        appropriate error value
    */
    if (strcmp(argv[CMD_GAME_IDX], PINOCHLE_NAME_STR) == 0)
    {
        if (num_players != PINOCHLE_PLAYER_CT)
        {
            cout << usage_msg << endl;
            return IMPROPER_GAME_INPUT;
        }
    }
    /*
        Checking that if HoldEm is the desired game, the correct number of
        players are supplied, and if not  print out usage message and return
        appropriate error value
    */
    else if (strcmp(argv[CMD_GAME_IDX], HOLD_EM_NAME_STR) == 0)
    {
        if (num_players < MIN_HOLD_EM_PLAYER_CT || MAX_HOLD_EM_PLAYER_CT < num_players)
        {
            cout << usage_msg << endl;
            return IMPROPER_GAME_INPUT;
        }
    }
    // If neither game is supplied properly print out usage message and return appropriate error value
    else
    {
        cout << usage_msg << endl;
        return IMPROPER_GAME_INPUT;
    }

    // Create a shared pointer for the game
    shared_ptr<Game> p = create(argc, argv);

    // Make sure the pointer is not a nullptr
    if (p)
    {
        // Play the game
        try
        {
            p->play();
        }
        // Catch any runtime errors
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
            return GAME_PLAY_FAILURE;
        }
    }
    // If the pointer is a nullptr print out the error message and return the appropriate error value
    else
    {
        cout << make_error_msg << endl;
        return GAME_MAKE_FAILURE;
    }

    // If all goes well return success value
    return SUCCESS;
}