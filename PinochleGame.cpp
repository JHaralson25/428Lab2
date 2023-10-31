/*
    PinochleGame.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (PinochleGame.cpp) defines the methods of the PinochleGame class along
    with static member variables and an ostream insertion operator.
*/

// All includes
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

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
        // Print out the melds
        printMelds();
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
    cout << endl;
    cout << "PLAYERS" << endl;
    for (long unsigned int i = 0; i < hands.size(); ++i)
    {
        cout << "Player: " << names[i] << endl;
        hands[i].print(cout, PINOCHLE_DEAL_SIZE);
        cout << endl;
    }
}

/*
    printMelds method for PinochleGame that prints out
    the melds of all the players alongside their names
*/
void PinochleGame::printMelds()
{
    cout << "MELDS" << endl;
    vector<PinochleMelds> pinochleCombos;
    for (long unsigned int i = 0; i < hands.size(); ++i)
    {
        pinochleCombos.clear();
        suit_independent_evaluation(hands[i], pinochleCombos);
        cout << "Player " << names[i] << ":" << endl;
        for (long unsigned int j = 0; j < pinochleCombos.size(); ++j)
        {
            cout << "   " << pinochleCombos[j];
        }
    }
    cout << endl;
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

/*
    Array that stores each meld within the enum class respective point values
*/
int PinochleGame::pointValues[] = {
    10,   // dix
    20,   // offsuitmarriage
    40,   // fortyjacks
    40,   // pinochle
    40,   // insuitmarriage
    60,   // sixtyqueens
    80,   // eightykings
    100,  // hundredaces
    150,  // insuitrun
    300,  // doublepinochle
    400,  // fourhundredjacks
    600,  // sixhundredqueens
    800,  // eighthundredkings
    1000, // thousandaces
    1500  // insuitdoublerun
};

/*
    Array that stores each meld within the enum class respective output strings
*/
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
    "insuitdoublerun"};

/*
    ostream insertion operator that takes a reference to an ostream and PinochleMeld
    and displays apprpriate information using the above defined arrays
*/
std::ostream &operator<<(ostream &os, const PinochleMelds &pm)
{
    os << PinochleGame::pointStrings[static_cast<int>(pm)] << " " << PinochleGame::pointValues[static_cast<int>(pm)] << endl;
    return os;
}

/*
    suit_independent_evaluation function that that takes a const reference to a CardSet and a reference to a vector of
    PinochleMelds, iterates through the vector of a copy of the CardSet, and pushes all the melds onto the vector
*/
void PinochleGame::suit_independent_evaluation(const CardSet<Suits, PinochleRanks> &cs, vector<PinochleMelds> &pms)
{
    /*
        Here we copy construct the provided CardSet so as to not interfere with original, and then obtain its private 
        vector member variable employing a scoped pointer.
    */
    CardSet<Suits, PinochleRanks> temp(cs);
    std::vector<Card <Suits, PinochleRanks> > CardSet<Suits, PinochleRanks>::*cardsPtr = CardSet<Suits, PinochleRanks>::getVector();
    std::vector<Card <Suits, PinochleRanks> > cardsRef = (temp.*cardsPtr);

    // Counting aces
    int as = 0;
    int ah = 0;
    int ad = 0;
    int ac = 0;

    // Counting kings
    int ks = 0;
    int kh = 0;
    int kd = 0;
    int kc = 0;

    // Counting queens
    int qs = 0;
    int qh = 0;
    int qd = 0;
    int qc = 0;

    // Counting jacks
    int js = 0;
    int jh = 0;
    int jd = 0;
    int jc = 0;

    // Iterating through hands
    for (long unsigned int i = 0; i < cardsRef.size(); ++i)
    {
        // We check by rank and then by suit
        if (cardsRef[i].rank == PinochleRanks::ace)
        {
            if (cardsRef[i].suit == Suits::spades)
            {
                ++as;
            }
            else if (cardsRef[i].suit == Suits::hearts)
            {
                ++ah;
            }
            else if (cardsRef[i].suit == Suits::diamonds)
            {
                ++ad;
            }
            else if (cardsRef[i].suit == Suits::clubs)
            {
                ++ac;
            }
        }
        else if (cardsRef[i].rank == PinochleRanks::king)
        {
            if (cardsRef[i].suit == Suits::spades)
            {
                ++ks;
            }
            else if (cardsRef[i].suit == Suits::hearts)
            {
                ++kh;
            }
            else if (cardsRef[i].suit == Suits::diamonds)
            {
                ++kd;
            }
            else if (cardsRef[i].suit == Suits::clubs)
            {
                ++kc;
            }
        }
        else if (cardsRef[i].rank == PinochleRanks::queen)
        {
            if (cardsRef[i].suit == Suits::spades)
            {
                ++qs;
            }
            else if (cardsRef[i].suit == Suits::hearts)
            {
                ++qh;
            }
            else if (cardsRef[i].suit == Suits::diamonds)
            {
                ++qd;
            }
            else if (cardsRef[i].suit == Suits::clubs)
            {
                ++qc;
            }
        }
        else if (cardsRef[i].rank == PinochleRanks::jack)
        {
            if (cardsRef[i].suit == Suits::spades)
            {
                ++js;
            }
            else if (cardsRef[i].suit == Suits::hearts)
            {
                ++jh;
            }
            else if (cardsRef[i].suit == Suits::diamonds)
            {
                ++jd;
            }
            else if (cardsRef[i].suit == Suits::clubs)
            {
                ++jc;
            }
        }
    }

    // Checking aces
    if (as == PINOCHLE_MAJOR_CT && ah == PINOCHLE_MAJOR_CT && ad == PINOCHLE_MAJOR_CT && ac == PINOCHLE_MAJOR_CT)
    {
        pms.push_back(PinochleMelds::thousandaces);
    }
    else if (as >= PINOCHLE_MINOR_CT && ah >= PINOCHLE_MINOR_CT && ad >= PINOCHLE_MINOR_CT && ac >= PINOCHLE_MINOR_CT)
    {
        pms.push_back(PinochleMelds::hundredaces);
    }

    // Checking kings
    if (ks == PINOCHLE_MAJOR_CT && kh == PINOCHLE_MAJOR_CT && kd == PINOCHLE_MAJOR_CT && kc == PINOCHLE_MAJOR_CT)
    {
        pms.push_back(PinochleMelds::eighthundredkings);
    }
    else if (ks >= PINOCHLE_MINOR_CT && kh >= PINOCHLE_MINOR_CT && kd >= PINOCHLE_MINOR_CT && kc >= PINOCHLE_MINOR_CT)
    {
        pms.push_back(PinochleMelds::eightykings);
    }

    // Checking queens
    if (qs == PINOCHLE_MAJOR_CT && qh == PINOCHLE_MAJOR_CT && qd == PINOCHLE_MAJOR_CT && qc == PINOCHLE_MAJOR_CT)
    {
        pms.push_back(PinochleMelds::sixhundredqueens);
    }
    else if (qs >= PINOCHLE_MINOR_CT && qh >= PINOCHLE_MINOR_CT && qd >= PINOCHLE_MINOR_CT && qc >= PINOCHLE_MINOR_CT)
    {
        pms.push_back(PinochleMelds::sixtyqueens);
    }

    // Checking jacks
    if (js == PINOCHLE_MAJOR_CT && jh == PINOCHLE_MAJOR_CT && jd == PINOCHLE_MAJOR_CT && jc == PINOCHLE_MAJOR_CT)
    {
        pms.push_back(PinochleMelds::fourhundredjacks);
    }
    else if (js >= PINOCHLE_MINOR_CT && jh >= PINOCHLE_MINOR_CT && jd >= PINOCHLE_MINOR_CT && jc >= PINOCHLE_MINOR_CT)
    {
        pms.push_back(PinochleMelds::fortyjacks);
    }

    // Checking for pinochle combos
    if (jd == PINOCHLE_MAJOR_CT && qs == PINOCHLE_MAJOR_CT)
    {
        pms.push_back(PinochleMelds::doublepinochle);
    }
    else if (jd >= PINOCHLE_MINOR_CT && qs >= PINOCHLE_MINOR_CT)
    {
        pms.push_back(PinochleMelds::pinochle);
    }
}