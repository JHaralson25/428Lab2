/*
    HoldEmGame.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (HoldEmGame.h) declares the enum for HoldEmState, its operators,
    and the HoldEmGame class, alongside its 4 member variables,
    6 member functions, and public constructor.
*/

// All includes
#pragma once

#include <vector>
#include <string>

#include "Suit.h"
#include "Game.h"
#include "CardSet_T.h"
#include "HoldEmDeck.h"

// HoldEmState enum declaration
enum class HoldEmState
{
    preflop,
    flop,
    turn,
    river,
    undefined
};

enum class HoldEmHandRank {
    xhigh,
    pair,
    twopair,
    threeofakind,
    straight,
    flush,
    fullhouse,
    fourofakind,
    straightflush,
    undefined
};

// HoldEmState overloaded operators
ostream &operator<<(ostream &os, const HoldEmState &hes);
HoldEmState &operator++(HoldEmState &hes);

/*
    HoldEmGame class declaration, alongside its 4 member variables,
    6 member functions, and public constructor
*/
class HoldEmGame : public Game
{
    // Public constructor and play method
    public:
        HoldEmGame(int argc, const char *argv[]);
        virtual int play();
        static string stringVals[];
        friend std::ostream& operator<<(ostream& os, const HoldEmHandRank& hehr);

        struct HandInfo {
            HandInfo(CardSet <Suits, HoldEmRanks> h, std::string n, HoldEmHandRank hr);

            CardSet <Suits, HoldEmRanks> hand;
            std::string name;
            HoldEmHandRank handRank;
        };
    protected:
        // Protected member variables
        HoldEmDeck hed;
        HoldEmState hes;
        std::vector<CardSet <Suits, HoldEmRanks> > hands;
        CardSet<Suits, HoldEmRanks> board;

        // Protected member functions
        virtual void deal();
        void printPlayers();
        void printBoard();
        void collectHands();
        void collectBoard();
    private:
        HoldEmHandRank holdem_hand_evaluation(const CardSet<Suits, HoldEmRanks> &hand);
};

// HandInfo overloaded operators
bool operator<(const HoldEmGame::HandInfo& hi1, const HoldEmGame::HandInfo& hi2);
