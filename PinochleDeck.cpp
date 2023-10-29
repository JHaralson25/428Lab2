/*
    PinochleDeck.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (PinochleDeck.cpp) defines an ostream insertion operator,
    a prefix increment operator, and a default constructor.
*/

// All includes
#include <iostream>
#include <vector>
using namespace std;

#include "Suit.h"
#include "Card_T.h"
#include "PinochleDeck.h"

/*
    Definition of the PinochleDeck default constructor.
    It adds "Cards" to the inherited vector member variable.
*/
PinochleDeck::PinochleDeck()
{
    // Creates instances of rank and suit enums
    PinochleRanks p;
    Suits s = Suits::clubs;

    // Loops through ranks and suits and adds two of each combination
    do
    {
        p = PinochleRanks::nine;
        do
        {
            cards.push_back(Card(s, p));
            cards.push_back(Card(s, p));
            ++p;
        } while (p != PinochleRanks::undefined);
        ++s;
    } while (s != Suits::undefined);
}

/*
    Definition of the overloaded PinochleDeck ostream insertion operator.
    Prints number/symbol to the ostream and returns the ostream.
*/
ostream &operator<<(ostream &os, const PinochleRanks &pr)
{
    switch (pr)
    {
    case PinochleRanks::nine:
        os << "9";
        break;
    case PinochleRanks::jack:
        os << "J";
        break;
    case PinochleRanks::queen:
        os << "Q";
        break;
    case PinochleRanks::king:
        os << "K";
        break;
    case PinochleRanks::ten:
        os << "10";
        break;
    case PinochleRanks::ace:
        os << "A";
        break;
    case PinochleRanks::undefined:
        os << "?";
        break;
    }
    return os;
}

/*
    Definition of the overloaded PinochleDeck prefix insertion operator.
    Increments rank to next rank via a switch statement.
*/
PinochleRanks &operator++(PinochleRanks &pr)
{
    switch (pr)
    {
    case PinochleRanks::nine:
        pr = PinochleRanks::jack;
        break;
    case PinochleRanks::jack:
        pr = PinochleRanks::queen;
        break;
    case PinochleRanks::queen:
        pr = PinochleRanks::king;
        break;
    case PinochleRanks::king:
        pr = PinochleRanks::ten;
        break;
    case PinochleRanks::ten:
        pr = PinochleRanks::ace;
        break;
    case PinochleRanks::ace:
        pr = PinochleRanks::undefined;
        break;
    case PinochleRanks::undefined:
        pr = PinochleRanks::undefined;
        break;
    }
    return pr;
}