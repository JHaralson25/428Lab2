/*
    PinochleGame.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (PinochleGame.h) declares the PinochleGame class,
    alongside its 2 member variables, 4 member functions,
    and a public constructor.
*/

// All includes
#pragma once

#include <vector>
#include <string>

#include "Suit.h"
#include "Game.h"
#include "CardSet_T.h"
#include "PinochleDeck.h"

/*
    PinochleGame class declaration, alongside its 2 member variables,
    4 member functions, and public constructor.
*/
class PinochleGame : public Game
{
    // Public constructor and play method
    public:
        PinochleGame(int argc, const char *argv[]);
        virtual int play();

        static int pointValues[];
    protected:
        // Protected member variables
        PinochleDeck pd;
        std::vector<CardSet <Suits, PinochleRanks> > hands;

        // Protected member functions
        virtual void deal();
        void printPlayers();
        void collectHands();
};

enum class PinochleMelds {
    dix,
    offsuitmarriage,
    fortyjacks,
    pinochle,
    insuitmarriage,
    sixtyqueens,
    eightykings,
    hundredaces,
    insuitrun,
    doublepinochle,
    fourhundredjacks,
    sixhundredqueens,
    eighthundredkings,
    thousandaces,
    insuitdoublerun
};