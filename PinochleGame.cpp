/*
    PinochleGame.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (PinochleGame.cpp) defines the methods of the PinochleGame class.
*/

// All includes
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "Suit.h"
#include "Game.h"
#include "CardSet_T.h"
#include "PinochleGame.h"
#include "GlobalValues.h"

/*
    Constructor for PinochleGame that employs user inputs
    argc and argv, and uses said inputs to create hands
    for the players.
*/
PinochleGame::PinochleGame(int argc, const char *argv[]) : Game(argc, argv)
{
    for (int i = CMD_START_IDX; i < argc; ++i)
    {
        hands.push_back(CardSet<Suits, PinochleRanks>());
    }
}

/*
    Play method for PinochleGame that starts a game and
    loops through various parts of the game (using helper methods)
    until and end condition is satisfied.
*/
int PinochleGame::play()
{
    while (true)
    {
        // Shuffle the deck
        pd.shuffle();
        // Deal cards
        deal();
        // Print out the players and their hands
        printPlayers();
        // Collect the players' hands
        collectHands();
        // End the game if applicable
        if (terminateGame())
        {
            return SUCCESS;
        }
    }
}

/*
    Deal method for PinochleGame that continutes to deal cards
    to players evenly until the deck is empty
*/
void PinochleGame::deal()
{
    while (!pd.is_empty())
    {
        for (long unsigned int i = 0; i < hands.size(); ++i)
        {
            for (int j = 0; j < PINOCHLE_DEAL_SIZE; ++j)
            {
                if (!pd.is_empty())
                {
                    pd >> hands[i];
                }
            }
        }
    }
}

/*
    printPlayers method for PinochleGame that prints out
    the names of all the players alongside their hand
*/
void PinochleGame::printPlayers()
{
    for (long unsigned int i = 0; i < hands.size(); ++i)
    {
        cout << "Player: " << names[i] << endl;
        hands[i].print(cout, PINOCHLE_DEAL_SIZE);
        cout << endl;
    }
}

/*
    collectHands method for PinochleGame that collects
    the cards from all the players and puts them
    back into the deck
*/
void PinochleGame::collectHands()
{
    for (long unsigned int i = 0; i < hands.size(); ++i)
    {
        pd.collect(hands[i]);
    }
}

int PinochleGame::pointValues[] = {
    10,     // dix
    20,     // offsuitmarriage
    40,     // fortyjacks
    40,     // pinochle
    40,     // insuitmarriage
    60,     // sixtyqueens
    80,     // eightykings
    100,    // hundredaces
    150,    // insuitrun
    300,    // doublepinochle
    400,    // fourhundredjacks
    600,    // sixhundredqueens
    800,    // eighthundredkings
    1000,   // thousandaces
    1500    // insuitdoublerun
};

string PinochleGame::pointStrings[] = {
    "dix",  
    "offsuitmarriage",   
    "fortyjacks",  
    "pinochle",   
    "insuitmarriage",   
    "sixtyqueens",   
    "eightykings",   
    "hundredaces", 
    "insuitrun", 
    "doublepinochke",  
    "fourhundredjacks",  
    "sixhundredqueens",  
    "eighthundredkings",  
    "thousandaces", 
    "insuitdoublerun"  
};

PinochleGame operator<<(ostream & os, const PinochleMelds & pm){
    cout << PinochleGame::pointStrings[static_cast<int>(pm)] << " " <<PinochleGame::pointValues[static_cast<int>(pm)] << endl;
}