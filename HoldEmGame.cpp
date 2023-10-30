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
#include <algorithm>

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

string HoldEmGame::stringVals[] = {
    "xhigh",
    "pair",
    "twopair",
    "threeofakind",
    "straight",
    "flush",
    "fullhouse",
    "fourofakind",
    "straightflush",
    "undefined"
};

std::ostream& operator<<(ostream& os, const HoldEmHandRank& hehr)
{
    os << HoldEmGame::stringVals[static_cast<int>(hehr)] << endl;
    return os;
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<Suits, HoldEmRanks> &hand) {
    CardSet<Suits, HoldEmRanks> temp(hand);
    vector<Card <Suits, HoldEmRanks> > CardSet<Suits, HoldEmRanks>::* cardsPtr = CardSet<Suits, HoldEmRanks>::getVector();
    vector<Card <Suits, HoldEmRanks> > cardsRef = (temp.*cardsPtr);

    sort(cardsRef.begin(), cardsRef.end(), lessRank<Suits, HoldEmRanks>);
    sort(cardsRef.begin(), cardsRef.end(), lessSuit<Suits, HoldEmRanks>);

    if (cardsRef.size() != 5) {
        return HoldEmHandRank::undefined;
    }
    int numClubs = 0;
    int numSpades = 0;
    int numDiamonds = 0;
    int numHearts = 0;
    for (auto i : cardsRef) {
        if (i.suit == Suits::clubs) {
            ++numClubs;
        }
        if (i.suit == Suits::spades) {
            ++numSpades;
        }
        if (i.suit == Suits::diamonds) {
            ++numDiamonds;
        }
        if (i.suit == Suits::hearts) {
            ++numHearts;
        }
    }
    //Check for straightflush
    if (numClubs == 5 || numSpades == 5 || numDiamonds == 5 || numHearts == 5) {
        if ((++(cardsRef[0].rank) == cardsRef[1].rank) && (++(cardsRef[1].rank) == cardsRef[2].rank) && (++(cardsRef[2].rank) == cardsRef[3].rank) && (++(cardsRef[3].rank) == cardsRef[4].rank)) {
            return HoldEmHandRank::straightflush;
        }
        if (cardsRef[0].rank == HoldEmRanks::two && cardsRef[1].rank == HoldEmRanks::three && cardsRef[2].rank == HoldEmRanks::four && cardsRef[3].rank == HoldEmRanks::five && cardsRef[4].rank == HoldEmRanks::ace) {
            return HoldEmHandRank::straightflush;
        }
    }

    //check for four of a kind
    if ((cardsRef[0].rank == cardsRef[1].rank && cardsRef[1].rank == cardsRef[2].rank && cardsRef[2].rank == cardsRef[3].rank) || ((cardsRef[1].rank == cardsRef[2].rank && cardsRef[2].rank == cardsRef[3].rank) && cardsRef[3].rank == cardsRef[4].rank)) {
        return HoldEmHandRank::fourofakind;
    }

    //check for fullhouse
    if (((cardsRef[0].rank == cardsRef[1].rank && cardsRef[1].rank == cardsRef[2].rank) && (cardsRef[3].rank == cardsRef[4].rank)) || ((cardsRef[2].rank == cardsRef[3].rank && cardsRef[3].rank == cardsRef[4].rank) && (cardsRef[0].rank == cardsRef[1].rank))) {
        return HoldEmHandRank::fullhouse;
    }

    //Check for flush
    if (numClubs == 5 || numSpades == 5 || numDiamonds == 5 || numHearts == 5) {
        return HoldEmHandRank::flush;
    }

    //checks for straight
    if ((++(cardsRef[0].rank) == cardsRef[1].rank) && (++(cardsRef[1].rank) == cardsRef[2].rank) && (++(cardsRef[2].rank) == cardsRef[3].rank) && (++(cardsRef[3].rank) == cardsRef[4].rank)) {
        return HoldEmHandRank::straight;
    }
    if (cardsRef[0].rank == HoldEmRanks::two && cardsRef[1].rank == HoldEmRanks::three && cardsRef[2].rank == HoldEmRanks::four && cardsRef[3].rank == HoldEmRanks::five && cardsRef[4].rank == HoldEmRanks::ace) {
        return HoldEmHandRank::straight;
    }

    //checks for three of a kind
    if (cardsRef[0].rank == cardsRef[1].rank && cardsRef[1].rank == cardsRef[2].rank) {
        return HoldEmHandRank::threeofakind;
    }
    if (cardsRef[1].rank == cardsRef[2].rank && cardsRef[2].rank == cardsRef[3].rank) {
        return HoldEmHandRank::threeofakind;
    }
    if (cardsRef[2].rank == cardsRef[3].rank && cardsRef[3].rank == cardsRef[4].rank) {
        return HoldEmHandRank::threeofakind;
    }

    //Check for twopair
    if ((cardsRef[0].rank == cardsRef[1].rank) && (cardsRef[2].rank == cardsRef[3].rank )) {
        return HoldEmHandRank::twopair;
    }
    if ((cardsRef[0].rank == cardsRef[1].rank) && (cardsRef[3].rank == cardsRef[4].rank )) {
        return HoldEmHandRank::twopair;
    }
    if ((cardsRef[1].rank == cardsRef[2].rank) && (cardsRef[3].rank == cardsRef[4].rank)) {
        return HoldEmHandRank::twopair;
    }


    //check for pair
    if ((cardsRef[0].rank == cardsRef[1].rank) || (cardsRef[1].rank == cardsRef[2].rank) || (cardsRef[2].rank == cardsRef[3].rank) || (cardsRef[3].rank == cardsRef[4].rank)) {
        return HoldEmHandRank::pair;
    }

    //default
    return HoldEmHandRank::xhigh;

    
}