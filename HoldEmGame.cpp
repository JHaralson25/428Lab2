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

bool operator<(const HoldEmGame::HandInfo &hi1, const HoldEmGame::HandInfo &hi2)
{
    /*
        Here we copy construct the provided CardSets so as to not interfere with originals, and then obtain their private 
        vector member variable employing a scoped pointer.
    */
    CardSet<Suits, HoldEmRanks> temp1(hi1.hand);
    CardSet<Suits, HoldEmRanks> temp2(hi2.hand);
    vector<Card <Suits, HoldEmRanks> > CardSet<Suits, HoldEmRanks>::*cardsPtr1 = CardSet<Suits, HoldEmRanks>::getVector();
    vector<Card <Suits, HoldEmRanks> > CardSet<Suits, HoldEmRanks>::*cardsPtr2 = CardSet<Suits, HoldEmRanks>::getVector();
    vector<Card <Suits, HoldEmRanks> > cardsRef1 = (temp1.*cardsPtr1);
    vector<Card <Suits, HoldEmRanks> > cardsRef2 = (temp2.*cardsPtr2);

    // Sort the vectors in order to better rank the cards
    sort(cardsRef1.begin(), cardsRef1.end(), lessRank<Suits, HoldEmRanks>);
    sort(cardsRef2.begin(), cardsRef2.end(), lessRank<Suits, HoldEmRanks>);

    // Check that the correct number of cards exist in both hands
    if (cardsRef1.size() != HOLD_EM_TOTAL_HAND_SIZE)
    {
        return false;
    }

    if (cardsRef2.size() != HOLD_EM_TOTAL_HAND_SIZE)
    {
        return false;
    }

    // Immeadiatly return of the rank is less than the other rank or switch
    if (hi1.handRank < hi2.handRank)
    {
        return true;
    }
    else if (hi1.handRank > hi2.handRank)
    {
        return false;
    }

    // Check pairs
    if (hi1.handRank == HoldEmHandRank::pair && hi2.handRank == HoldEmHandRank::pair)
    {
        // Get location of first pair
        int pairPos1;
        for (int i = 0; i < HOLD_EM_PAIR_POS; ++i)
        {
            if (cardsRef1[i].rank == cardsRef1[i + 1].rank)
            {
                pairPos1 = i;
                break;
            }
        }

        // Get location of second pair
        int pairPos2;
        for (int i = 0; i < HOLD_EM_PAIR_POS; ++i)
        {
            if (cardsRef2[i].rank == cardsRef2[i + 1].rank)
            {
                pairPos2 = i;
                break;
            }
        }

        // Check ordering of pairs
        if (cardsRef1[pairPos1].rank < cardsRef2[pairPos2].rank)
        {
            return true;
        }
        else if (cardsRef1[pairPos1].rank > cardsRef2[pairPos2].rank)
        {
            return false;
        }

        // Otherwise check high card
        for (int i = HOLD_EM_TOTAL_HAND_SIZE - 1; i > -1; --i)
        {
            if (cardsRef1[i].rank < cardsRef2[i].rank)
            {
                return true;
            }
            else if (cardsRef1[i].rank > cardsRef2[i].rank)
            {
                return false;
            }
        }

        // Return false by default
        return false;
    }

    // Check situation of two pairs
    if (hi1.handRank == HoldEmHandRank::twopair && hi2.handRank == HoldEmHandRank::twopair)
    {
        // Get locations of both pairs for first hand
        int stPairPos1 = -1;
        int ndPairPos1 = -1;
        for (int i = 0; i < HOLD_EM_PAIR_POS; ++i)
        {
            if (cardsRef1[i].rank == cardsRef1[i + 1].rank)
            {
                if (stPairPos1 == -1)
                {
                    stPairPos1 = i;
                }
                else
                {
                    ndPairPos1 = i;
                    break;
                }
            }
        }

        // Get locations of both pairs for second hand
        int stPairPos2 = -1;
        int ndPairPos2 = -1;
        for (int i = 0; i < HOLD_EM_PAIR_POS; ++i)
        {
            if (cardsRef2[i].rank == cardsRef2[i + 1].rank)
            {
                if (stPairPos2 == -1)
                {
                    stPairPos2 = i;
                }
                else
                {
                    ndPairPos2 = i;
                    break;
                }
            }
        }

        // Check ordering of first and second pair and return accordingly
        if (cardsRef1[stPairPos1].rank < cardsRef2[stPairPos2].rank)
        {
            return true;
        }
        else if (cardsRef1[stPairPos1].rank > cardsRef2[stPairPos2].rank)
        {
            return false;
        }

        if (cardsRef1[ndPairPos1].rank < cardsRef2[ndPairPos2].rank)
        {
            return true;
        }
        else if (cardsRef1[ndPairPos1].rank > cardsRef2[ndPairPos2].rank)
        {
            return false;
        }

        // Otherwise check high card
        for (int i = HOLD_EM_TOTAL_HAND_SIZE - 1; i > -1; --i)
        {
            if (cardsRef1[i].rank < cardsRef2[i].rank)
            {
                return true;
            }
            else if (cardsRef1[i].rank > cardsRef2[i].rank)
            {
                return false;
            }
        }

        // Return false by default
        return false;
    }

    // Logic for three of a kind and full house is the same so combine
    if ((hi1.handRank == HoldEmHandRank::threeofakind && hi2.handRank == HoldEmHandRank::threeofakind) || 
    (hi1.handRank == HoldEmHandRank::fullhouse && hi2.handRank == HoldEmHandRank::fullhouse))
    {
        // Get location of first tripple
        int threePos1;
        for (int i = 0; i < HOLD_EM_TRIP_POS; ++i)
        {
            if (cardsRef1[i].rank == cardsRef1[i + 1].rank && cardsRef1[i + 1].rank == cardsRef1[i + 2].rank)
            {
                threePos1 = i;
                break;
            }
        }

        // Get location of second tripple
        int threePos2;
        for (int i = 0; i < HOLD_EM_TRIP_POS; ++i)
        {
            if (cardsRef2[i].rank == cardsRef2[i + 1].rank && cardsRef2[i + 1].rank == cardsRef2[i + 2].rank)
            {
                threePos2 = i;
                break;
            }
        }

        // Compare ranks of tripples
        if (cardsRef1[threePos1].rank < cardsRef2[threePos2].rank)
        {
            return true;
        }
        else if (cardsRef1[threePos1].rank > cardsRef2[threePos2].rank)
        {
            return false;
        }

        // Otherwise check high card (did not ask but did anyway see readme)
        for (int i = HOLD_EM_TOTAL_HAND_SIZE - 1; i > -1; --i)
        {
            if (cardsRef1[i].rank < cardsRef2[i].rank)
            {
                return true;
            }
            else if (cardsRef1[i].rank > cardsRef2[i].rank)
            {
                return false;
            }
        }

        // Return false by default
        return false;
    }

    // Logic for straight and straight flush is the same
    if ((hi1.handRank == HoldEmHandRank::straight && hi2.handRank == HoldEmHandRank::straight) || 
    (hi1.handRank == HoldEmHandRank::straightflush && hi2.handRank == HoldEmHandRank::straightflush))
    {
        // Just check first card as they are already confirmed to be straights or straights flushes
        if (cardsRef1[0].rank < cardsRef2[0].rank)
        {
            return true;
        }

        // Return false by default
        return false;
    }

    // Logic for flush and xhigh are the same so combine
    if ((hi1.handRank == HoldEmHandRank::flush && hi2.handRank == HoldEmHandRank::flush) || 
    (hi1.handRank == HoldEmHandRank::xhigh && hi2.handRank == HoldEmHandRank::xhigh))
    {
        // Just checkl high card for both
        for (int i = HOLD_EM_TOTAL_HAND_SIZE - 1; i > -1; --i)
        {
            if (cardsRef1[i].rank < cardsRef2[i].rank)
            {
                return true;
            }
            else if (cardsRef1[i].rank > cardsRef2[i].rank)
            {
                return false;
            }
        }

        // Return false by default
        return false;
    }

    // Logic for four of a kind
    if (hi1.handRank == HoldEmHandRank::fourofakind && hi2.handRank == HoldEmHandRank::fourofakind)
    {
        // Get location of four of a kind for first hand
        int fourPos1;
        for (int i = 0; i < HOLD_EM_QUAD_POS; ++i)
        {
            if (cardsRef1[i].rank == cardsRef1[i + 1].rank && cardsRef1[i + 1].rank == cardsRef1[i + 2].rank && cardsRef1[i + 2].rank == cardsRef1[i + 3].rank)
            {
                fourPos1 = i;
                break;
            }
        }

        // Get location of four of a kind for second hand
        int fourPos2;
        for (int i = 0; i < HOLD_EM_QUAD_POS; ++i)
        {
            if (cardsRef2[i].rank == cardsRef2[i + 1].rank && cardsRef2[i + 1].rank == cardsRef2[i + 2].rank && cardsRef2[i + 2].rank == cardsRef2[i + 3].rank)
            {
                fourPos2 = i;
                break;
            }
        }

        // Compare 4 of a kinds and check ranks
        if (cardsRef1[fourPos1].rank < cardsRef2[fourPos2].rank)
        {
            return true;
        }
        else if (cardsRef1[fourPos1].rank > cardsRef2[fourPos2].rank)
        {
            return false;
        }

        // Check high card (this was not asked but we did it anyway see readme)
        for (int i = HOLD_EM_TOTAL_HAND_SIZE - 1; i > -1; --i)
        {
            if (cardsRef1[i].rank < cardsRef2[i].rank)
            {
                return true;
            }
            else if (cardsRef1[i].rank > cardsRef2[i].rank)
            {
                return false;
            }
        }

        // Return false by default
        return false;
    }

    // Return false by default
    return false;
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

HoldEmGame::HandInfo::HandInfo(CardSet<Suits, HoldEmRanks> h, std::string n, HoldEmHandRank hr) : hand(h), name(n), handRank(hr) {}

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
        // Check winner after flop
        checkWinner();
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
    checkWinner method for checking and printing the winner of all the players
    given HandInfo structs containing hands, names, and ranks.
*/
void HoldEmGame::checkWinner()
{
    // Create vector of HandInfo objects for players
    vector<HandInfo> handsInfo;
    for (long unsigned int i = 0; i < hands.size(); ++i)
    {
        handsInfo.push_back(HandInfo(hands[i], names[i], HoldEmHandRank::undefined));
    }

    // Loop through and add cards from board to HandInfo objects and rank the hands
    for (long unsigned int i = 0; i < handsInfo.size(); ++i)
    {
        // Copy construct board copy and add to HandInfo
        CardSet<Suits, HoldEmRanks> temp(board);
        while (!temp.is_empty())
        {
            temp >> handsInfo[i].hand;
        }
        // Rank the hand
        handsInfo[i].handRank = holdem_hand_evaluation(handsInfo[i].hand);
    }

    // Sort the vector of HandInfo structs
    sort(handsInfo.begin(), handsInfo.end());

    // Print out sorted HandInfo structs
    cout << endl;
    for (long unsigned int i = 0; i < handsInfo.size(); ++i)
    {
        cout << "Name: " << handsInfo[i].name << endl;
        cout << "Hand: ";
        handsInfo[i].hand.print(cout, HOLD_EM_TOTAL_HAND_SIZE);
        cout << "Rank: " << handsInfo[i].handRank << endl;
    }
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
    "undefined"};

std::ostream &operator<<(ostream &os, const HoldEmHandRank &hehr)
{
    os << HoldEmGame::stringVals[static_cast<int>(hehr)] << endl;
    return os;
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<Suits, HoldEmRanks> &hand)
{
    CardSet<Suits, HoldEmRanks> temp(hand);
    vector<Card <Suits, HoldEmRanks> > CardSet<Suits, HoldEmRanks>::*cardsPtr = CardSet<Suits, HoldEmRanks>::getVector();
    vector<Card <Suits, HoldEmRanks> > cardsRef = (temp.*cardsPtr);

    sort(cardsRef.begin(), cardsRef.end(), lessRank<Suits, HoldEmRanks>);

    if (cardsRef.size() != HOLD_EM_TOTAL_HAND_SIZE)
    {
        return HoldEmHandRank::undefined;
    }

    int numClubs = 0;
    int numSpades = 0;
    int numDiamonds = 0;
    int numHearts = 0;
    for (auto i : cardsRef)
    {
        if (i.suit == Suits::clubs)
        {
            ++numClubs;
        }
        if (i.suit == Suits::spades)
        {
            ++numSpades;
        }
        if (i.suit == Suits::diamonds)
        {
            ++numDiamonds;
        }
        if (i.suit == Suits::hearts)
        {
            ++numHearts;
        }
    }

    // Check for four of a kind
    for (int i = 0; i < HOLD_EM_QUAD_POS; ++i)
    {
        if (cardsRef[i].rank == cardsRef[i + 1].rank && cardsRef[i + 1].rank == cardsRef[i + 2].rank && cardsRef[i + 2].rank == cardsRef[i + 3].rank)
        {
            return HoldEmHandRank::fourofakind;
        }
    }

    // Check for fullhouse
    if (((cardsRef[0].rank == cardsRef[1].rank && cardsRef[1].rank == cardsRef[2].rank) && (cardsRef[3].rank == cardsRef[4].rank)) || ((cardsRef[2].rank == cardsRef[3].rank && cardsRef[3].rank == cardsRef[4].rank) && (cardsRef[0].rank == cardsRef[1].rank)))
    {
        return HoldEmHandRank::fullhouse;
    }

    // Check for three of a kind
    for (int i = 0; i < HOLD_EM_TRIP_POS; ++i)
    {
        if (cardsRef[i].rank == cardsRef[i + 1].rank && cardsRef[i + 1].rank == cardsRef[i + 2].rank)
        {
            return HoldEmHandRank::threeofakind;
        }
    }

    // Check for twopair
    bool foundFirstPair = false;
    for (int i = 0; i < HOLD_EM_PAIR_POS; ++i)
    {
        if (cardsRef[i].rank == cardsRef[i + 1].rank)
        {
            if (!foundFirstPair)
            {
                foundFirstPair = true;
            }
            else
            {
                return HoldEmHandRank::twopair;
            }
        }
    }

    // Check for pair
    for (int i = 0; i < HOLD_EM_PAIR_POS; ++i)
    {
        if (cardsRef[i].rank == cardsRef[i + 1].rank)
        {
            return HoldEmHandRank::pair;
        }
    }

    // Check for straightflush/straight
    if (cardsRef[0].rank == HoldEmRanks::two && cardsRef[1].rank == HoldEmRanks::three && cardsRef[2].rank == HoldEmRanks::four && cardsRef[3].rank == HoldEmRanks::five && cardsRef[4].rank == HoldEmRanks::ace)
    {
        if (numClubs == HOLD_EM_TOTAL_HAND_SIZE || numSpades == HOLD_EM_TOTAL_HAND_SIZE || numDiamonds == HOLD_EM_TOTAL_HAND_SIZE || numHearts == HOLD_EM_TOTAL_HAND_SIZE)
        {
            return HoldEmHandRank::straightflush;
        }
        else
        {
            return HoldEmHandRank::straight;
        }
    }
    if ((++(cardsRef[0].rank) == cardsRef[1].rank) && (++(cardsRef[1].rank) == cardsRef[2].rank) && (++(cardsRef[2].rank) == cardsRef[3].rank) && (++(cardsRef[3].rank) == cardsRef[4].rank))
    {
        if (numClubs == HOLD_EM_TOTAL_HAND_SIZE || numSpades == HOLD_EM_TOTAL_HAND_SIZE || numDiamonds == HOLD_EM_TOTAL_HAND_SIZE || numHearts == HOLD_EM_TOTAL_HAND_SIZE)
        {
            return HoldEmHandRank::straightflush;
        }
        else
        {
            return HoldEmHandRank::straight;
        }
    }

    // Check for flush
    if (numClubs == HOLD_EM_TOTAL_HAND_SIZE || numSpades == HOLD_EM_TOTAL_HAND_SIZE || numDiamonds == HOLD_EM_TOTAL_HAND_SIZE || numHearts == HOLD_EM_TOTAL_HAND_SIZE)
    {
        return HoldEmHandRank::flush;
    }

    // Default
    return HoldEmHandRank::xhigh;
}
