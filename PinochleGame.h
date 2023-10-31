/*
    PinochleGame.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (PinochleGame.h) declares the PinochleGame class,
    alongside its 2 member variables, 5 member functions, a friended ostream insertion operator,
    and a public constructor.
*/

// All includes
#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Suit.h"
#include "Game.h"
#include "CardSet_T.h"
#include "PinochleDeck.h"

//declaration of enum class Pinochlemelds that contains the possible melds a player can have
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

std::ostream &operator<<(ostream& os, const PinochleMelds& pm);

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
        static string pointStrings[];
        friend std::ostream &operator<<(ostream& os, const PinochleMelds& pm);
    protected:
        // Protected member variables
        PinochleDeck pd;
        std::vector<CardSet <Suits, PinochleRanks> > hands;

        // Protected member functions
        virtual void deal();
        void printPlayers();
        void printMelds();
        void collectHands();
    private:
        void suit_independent_evaluation(const CardSet<Suits, PinochleRanks> & cs, vector<PinochleMelds> &pms);
};