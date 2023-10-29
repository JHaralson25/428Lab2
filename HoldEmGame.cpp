/*
    HoldEmGame.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (HoldEmGame.cpp) defines the methods of the HoldEmGame class,
    as well as the operators of the HoldEmState enum class.
*/

// All includes
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "Suit.h"
#include "Game.h"
#include "CardSet_T.h"
#include "HoldEmGame.h"
#include "GlobalValues.h"

/*
    Overloaded prefix increment operator for HoldEmState
    that employs switch statement and returns new state.
*/
HoldEmState &operator++(HoldEmState &hes)
{
    switch (hes)
    {
    case HoldEmState::preflop:
        hes = HoldEmState::flop;
        break;
    case HoldEmState::flop:
        hes = HoldEmState::turn;
        break;
    case HoldEmState::turn:
        hes = HoldEmState::river;
        break;
    case HoldEmState::river:
        hes = HoldEmState::undefined;
        break;
    case HoldEmState::undefined:
        hes = HoldEmState::undefined;
        break;
    }
    return hes;
}

/*
    Overloaded inerstion operator for HoldEmState
    that uses a switch statement and prints out
    an appropriate string.
*/
ostream &operator<<(ostream &os, const HoldEmState &hes)
{
    switch (hes)
    {
    case HoldEmState::preflop:
        os << "preflop";
        break;
    case HoldEmState::flop:
        os << "flop";
        break;
    case HoldEmState::turn:
        os << "turn";
        break;
    case HoldEmState::river:
        os << "river";
        break;
    case HoldEmState::undefined:
        os << "undefined";
        break;
    }
    return os;
}

/*
    Constructor for HoldEmGame that employs user inputs
    argc and argv, and uses said inputs to create hands
    for the players.
*/
HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv)
{
    for (int i = CMD_START_IDX; i < argc; ++i)
    {
        hands.push_back(CardSet<Suits, HoldEmRanks>());
    }
}

/*
    Play method for HoldEmGame that starts a game and
    loops through various parts of the game (using helper methods)
    until and end condition is satisfied.
*/
int HoldEmGame::play()
{
    while (true)
    {
        // Shuffle the deck
        hed.shuffle();
        // Set starting state of game state
        hes = HoldEmState::preflop;
        // Deal player cards
        deal();
        printPlayers();
        // Deal flop
        deal();
        // Deal turn
        deal();
        // Deal river
        deal();
        collectHands();
        collectBoard();
        if (terminateGame())
        {
            return SUCCESS;
        }
    }
}

/*
    Deal method for HoldEmGame that uses a switch statement
    to accodingly deal cards to players and then prints
    the current board
*/
void HoldEmGame::deal()
{
    switch (hes)
    {
    /*
        Preflop case of deal, where we deal out cards to players as long as the
        deck is not empty.
    */
    case HoldEmState::preflop:
        for (int i = 0; i < HOLD_EM_HAND_SIZE; ++i)
        {
            for (long unsigned int j = 0; j < hands.size(); ++j)
            {
                if (!hed.is_empty())
                {
                    hed >> hands[j];
                }
            }
        }
        ++hes;
        break;

    /*
        Flop case of deal, where (if possible) we lay down three cards
        on the board, print the board, and increment the state.
    */
    case HoldEmState::flop:
        for (int i = 0; i < HOLD_EM_FLOP_SIZE; ++i)
        {
            if (!hed.is_empty())
            {
                hed >> board;
            }
        }
        printBoard();
        ++hes;
        break;

    /*
        Turn case of deal, where (if possible) we lay down a card in the
        board, print the board, and increment the state.
    */
    case HoldEmState::turn:
        if (!hed.is_empty())
        {
            hed >> board;
        }
        printBoard();
        ++hes;
        break;

    /*
        River case of deal, where (if possible) we lay down a card in the
        board, print the board, and increment the state.
    */
    case HoldEmState::river:
        if (!hed.is_empty())
        {
            hed >> board;
        }
        printBoard();
        ++hes;
        break;

    // Undefined case of deal, where we simply break.
    case HoldEmState::undefined:
        break;
    }
    return;
}

/*
    printPlayers method for HoldEmGame that prints out
    the names of all the players alongside their hand
*/
void HoldEmGame::printPlayers()
{
    for (long unsigned int i = 0; i < hands.size(); ++i)
    {
        cout << "Player: " << names[i] << endl;
        hands[i].print(cout, HOLD_EM_HAND_SIZE);
        cout << endl;
    }
}

/*
    printBoard method for HoldEmGame that prints
    the current board of the game
*/
void HoldEmGame::printBoard()
{
    cout << "BOARD (" << hes << "): ";
    board.print(cout, board.get_size());
}

/*
    collectHands method for HoldEmGame that collects
    the cards from all the players and puts them
    back into the deck
*/
void HoldEmGame::collectHands()
{
    for (long unsigned int i = 0; i < hands.size(); ++i)
    {
        hed.collect(hands[i]);
    }
}

/*
    collectBoard method for HoldEmGame that collects
    the cards from the board and puts them back
    into the deck
*/
void HoldEmGame::collectBoard()
{
    hed.collect(board);
}