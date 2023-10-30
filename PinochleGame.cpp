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
#include <algorithm>

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

std::ostream &operator<<(ostream& os, const PinochleMelds& pm)
{
    os << PinochleGame::pointStrings[static_cast<int>(pm)] << PinochleGame::pointValues[static_cast<int>(pm)] << endl;
    return os;
}


PinochleMelds PinochleGame::suit_independent_evaluation(const CardSet<Suits, PinochleRanks> &cs, vector<PinochleMelds> pms)
{

        // invoke deep copy constructor
        CardSet<Suits, PinochleRanks> temp = CardSet(cs);
    auto vecPtr = CardSet<Suits, PinochleRanks>::getVector();
    vector<Card<Suits, PinochleRanks>> &cardsRef = temp.*vecPtr;
    sort(cardsRef.begin(), cardsRef.end(), lessRank);

    //counting aces
    int as  = 0;
    int ah = 0;
    int ad  = 0;
    int ac = 0;

    //counting kings
    int ks = 0;
    int kh = 0;
    int kd = 0;
    int kc = 0;

    //counting queens
    int qs = 0;
    int qh = 0;
    int qd = 0;
    int qc = 0;

    //counting jacks
    int js = 0;
    int jh = 0;
    int jd = 0;
    int jc = 0;

    //iterating through hands
    for (int i = 0; i < cardsRef.size(); ++i){
        if (cardsRef[i].rank == PinochleRanks::ace){
            if (cardsRef[i].suit == Suits::spades){
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

    //checking aces
    if (as == 2 && ah == 2 && ad == 2 && ac == 2) {
        pms.push_back(PinochleMelds::thousandaces);
    }
    else if (as >= 1 && ah >= 1 && ad >=1 && ac >= 1){
        pms.push_back(PinochleMelds::hundredaces);
    }

    //checking kings
    if (ks == 2 && kh == 2 && kd == 2 && kc == 2)
    {
        pms.push_back(PinochleMelds::eighthundredkings);
    }
    else if (ks >= 1 && kh >= 1 && kd >= 1 && kc >= 1)
    {
        pms.push_back(PinochleMelds::eightykings);
    }

    //checking queens
    if (qs == 2 && qh == 2 && qd == 2 && qc == 2)
    {
        pms.push_back(PinochleMelds::sixhundredqueens);
    }
    else if (qs >= 1 && qh >= 1 && qd >= 1 && qc >= 1)
    {
        pms.push_back(PinochleMelds::sixtyqueens);
    }

    // checking jacks
    if (js == 2 && jh == 2 && jd == 2 && jc == 2)
    {
        pms.push_back(PinochleMelds::fourhundredjacks);
    }
    else if (js >= 1 && jh >= 1 && jd >= 1 && jc >= 1)
    {
        pms.push_back(PinochleMelds::fortyjacks);
    }

    //checking for pinochle combos
    if (jd == 2 && qs == 2){
        pms.push_back(PinochleMelds::doublepinochle);
    }
    else if (jd >= 2 && qs >= 2){
        pms.push_back(PinochleMelds::pinochle);
    }

}




